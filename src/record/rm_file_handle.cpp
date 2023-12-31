#include "rm_file_handle.h"

/**

 * @brief 由Rid得到指向RmRecord的指针

 *

 * @param rid 指定记录所在的位置

 * @return std::unique_ptr<RmRecord>

 */

std::unique_ptr<RmRecord> RmFileHandle::get_record(const Rid &rid, Context *context) const {
    // Todo:

    // 1. 获取指定记录所在的page handle

    // 2. 初始化一个指向RmRecord的指针（赋值其内部的data和size）

    RmPageHandle pagehandle = fetch_page_handle(rid.page_no);  // 通过指定的Rid获取相应页面的句柄

    std::unique_ptr<RmRecord> recordptr{new RmRecord(
        file_hdr_.record_size,
        pagehandle.get_slot(
            rid.slot_no))};  // 创建一个std::unique_ptr<RmRecord>，指向一个RmRecord对象，使用页面句柄的get_slot方法获取记录的指针

    return recordptr;  // 返回记录的unique_ptr指针
}

/**

 * @brief 在该记录文件（RmFileHandle）中插入一条记录

 *

 * @param buf 要插入的数据的地址

 * @return Rid 插入记录的位置

 */

Rid RmFileHandle::insert_record(char *buf, Context *context) {
    // Todo:

    // 1. 获取当前未满的page handle

    // 2. 在page handle中找到空闲slot位置

    // 3. 将buf复制到空闲slot位置

    // 4. 更新page_handle.page_hdr中的数据结构

    // 注意考虑插入一条记录后页面已满的情况，需要更新file_hdr_.first_free_page_no

    RmPageHandle pagehandle = create_page_handle();  // 创建一个页面句柄

    int i = Bitmap::first_bit(0, pagehandle.bitmap, file_hdr_.num_records_per_page);  // 在页面中找到可用的插槽位置

    char *slot = pagehandle.get_slot(i);  // 获取该位置的插槽

    memcpy(slot, buf, file_hdr_.record_size);  // 将数据从buf复制到插槽

    Bitmap::set(pagehandle.bitmap, i);  // 在位图中设置相应的位，表示插槽已被占用

    pagehandle.page_hdr->num_records++;  // 增加页面中的记录计数

    if (pagehandle.page_hdr->num_records >=
        file_hdr_.num_records_per_page)  // 如果页面中的记录数超过每页最大记录数，更新文件头的下一个可用页号

    {
        file_hdr_.first_free_page_no = pagehandle.page_hdr->next_free_page_no;
    }

    return Rid{pagehandle.page->GetPageId().page_no, i};  // 返回表示插入记录位置的Rid
}

/**

 * @brief 在该记录文件（RmFileHandle）中删除一条指定位置的记录

 *

 * @param rid 要删除的记录所在的指定位置

 */

void RmFileHandle::delete_record(const Rid &rid, Context *context) {
    // Todo:

    // 1. 获取指定记录所在的page handle

    // 2. 更新page_handle.page_hdr中的数据结构

    // 注意考虑删除一条记录后页面未满的情况，需要调用release_page_handle()

    RmPageHandle pagehandle = fetch_page_handle(rid.page_no);  // 获取记录所在页面的句柄

    Bitmap::reset(pagehandle.bitmap, rid.slot_no);  // 在位图中重置指定插槽的位，表示插槽为空闲

    pagehandle.page_hdr->num_records--;  // 减少页面中的记录计数

    if (pagehandle.page_hdr->num_records ==
        file_hdr_.num_records_per_page - 1)  // 如果页面中的记录数为每页最大记录数减1，说明刚刚是满的，释放页面句柄

    {
        release_page_handle(pagehandle);
    }
}

/**

 * @brief 更新指定位置的记录

 *

 * @param rid 指定位置的记录

 * @param buf 新记录的数据的地址

 */

void RmFileHandle::update_record(const Rid &rid, char *buf, Context *context) {
    // Todo:

    // 1. 获取指定记录所在的page handle

    // 2. 更新记录

    RmPageHandle pagehandle = fetch_page_handle(rid.page_no);  // 获取包含指定记录的页面句柄

    char *slot = pagehandle.get_slot(rid.slot_no);  // 获取指定插槽的地址

    memcpy(slot, buf, file_hdr_.record_size);  // 将新记录数据从buf复制到插槽
}

/** -- 以下为辅助函数 -- */

/**

 * @brief 获取指定页面编号的page handle

 *

 * @param page_no 要获取的页面编号

 * @return RmPageHandle 返回给上层的page_handle

 * @note pin the page, remember to unpin it outside!

 */

RmPageHandle RmFileHandle::fetch_page_handle(int page_no) const {
    // Todo:

    // 使用缓冲池获取指定页面，并生成page_handle返回给上层

    // if page_no is invalid, throw PageNotExistError exception

    if (page_no == INVALID_PAGE_ID)  // 创建一个新的PageId，用于表示新页面

    {
        throw PageNotExistError("table name?", page_no);

    }

    else  // 从缓冲池管理器中获取指定页面的句柄

    {
        Page *page = buffer_pool_manager_->FetchPage(PageId{this->fd_, page_no});

        return RmPageHandle(&file_hdr_, page);  // 返回一个RmPageHandle对象，将文件头和页面传递给它
    }
}

/**

 * @brief 创建一个新的page handle

 *

 * @return RmPageHandle

 */

RmPageHandle RmFileHandle::create_new_page_handle() {
    // Todo:

    // 1.使用缓冲池来创建一个新page

    // 2.更新page handle中的相关信息

    // 3.更新file_hdr_

    // 创建一个新的PageId，用于表示新页面

    PageId *newpageid = new PageId;

    newpageid->fd = fd_;

    Page *newpage = buffer_pool_manager_->NewPage(newpageid);  // 创建一个RmPageHandle对象，将文件头和新页面传递给它

    RmPageHandle newPageHandle =
        RmPageHandle(&file_hdr_, newpage);  // 创建一个RmPageHandle对象，将文件头和新页面传递给它

    newPageHandle.page_hdr->next_free_page_no =
        file_hdr_.first_free_page_no;  // 设置新页面的下一个可用页面编号为文件头的first_free_page_no

    // 更新文件头的first_free_page_no和num_pages字段

    file_hdr_.first_free_page_no = newpageid->page_no;

    file_hdr_.num_pages++;

    return newPageHandle;  // 返回新页面句柄
}

/**

 * @brief 创建或获取一个空闲的page handle

 *

 * @return RmPageHandle 返回生成的空闲page handle

 * @note pin the page, remember to unpin it outside!

 */

RmPageHandle RmFileHandle::create_page_handle() {
    // Todo:

    // 1. 判断file_hdr_中是否还有空闲页

    //     1.1 没有空闲页：使用缓冲池来创建一个新page；可直接调用create_new_page_handle()

    //     1.2 有空闲页：直接获取第一个空闲页

    // 2. 生成page handle并返回给上层

    if (file_hdr_.first_free_page_no ==
        -1)  // 如果文件头的first_free_page_no为-1，说明没有空闲页面，需要创建新的页面句柄

    {
        return create_new_page_handle();

    }

    else  // 否则，获取指定页面编号的页面句柄，并返回该句柄

    {
        return fetch_page_handle(file_hdr_.first_free_page_no);
    }
}

/**

 * @brief 当page handle中的page从已满变成未满的时候调用

 *

 * @param page_handle

 * @note only used in delete_record()

 */

void RmFileHandle::release_page_handle(RmPageHandle &page_handle) {
    // Todo:

    // 当page从已满变成未满，考虑如何更新：

    // 1. page_handle.page_hdr->next_free_page_no

    // 2. file_hdr_.first_free_page_no

    page_handle.page_hdr->next_free_page_no =
        file_hdr_.first_free_page_no;  // 设置页面头的下一个可用页面编号为文件头的first_free_page_no

    file_hdr_.first_free_page_no = page_handle.page->GetPageId().page_no;  // 更新文件头的first_free_page_no为页面的页号
}

/**

 * @brief 用于事务的rollback操作

 *

 * @param rid record的插入位置

 * @param buf record的内容

 */

void RmFileHandle::insert_record(const Rid &rid, char *buf) {
    if (rid.page_no < file_hdr_.num_pages) {
        create_new_page_handle();
    }

    RmPageHandle pageHandle = fetch_page_handle(rid.page_no);

    Bitmap::set(pageHandle.bitmap, rid.slot_no);

    pageHandle.page_hdr->num_records++;

    if (pageHandle.page_hdr->num_records == file_hdr_.num_records_per_page) {
        file_hdr_.first_free_page_no = pageHandle.page_hdr->next_free_page_no;
    }

    char *slot = pageHandle.get_slot(rid.slot_no);

    memcpy(slot, buf, file_hdr_.record_size);

    buffer_pool_manager_->UnpinPage(pageHandle.page->GetPageId(), true);
}
