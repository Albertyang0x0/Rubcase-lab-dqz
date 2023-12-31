#include "ix_node_handle.h"

/**
 * @brief 在当前node中查找第一个>=target的key_idx
 *
 * @return key_idx，范围为[0,num_key)，如果返回的key_idx=num_key，则表示target大于最后一个key
 * @note 返回key index（同时也是rid index），作为slot no
 */
int IxNodeHandle::lower_bound(const char *target) const {
    // Todo:
    // 查找当前节点中第一个大于等于target的key，并返回key的位置给上层
    // 提示: 可以采用多种查找方式，如顺序遍历、二分查找等；使用ix_compare()函数进行比较

    // 获取键的数量
    int r = page_hdr->num_key;  // GetSize();
    int l = 0;

    // 二分查找
    while (l < r) {
        int mid = (l + r) / 2;

        if (ix_compare(get_key(mid), target, file_hdr->col_type, file_hdr->col_len) >= 0) {
            r = mid;

        } else {
            l = mid + 1;
        }
    }

    // 如果遍历完整个结点仍未找到大于等于target的键，返回num_keys
    return l;
}

/**
 * @brief 在当前node中查找第一个>target的key_idx
 *
 * @return key_idx，范围为[1,num_key)，如果返回的key_idx=num_key，则表示target大于等于最后一个key
 * @note 注意此处的范围从1开始
 */
int IxNodeHandle::upper_bound(const char *target) const {
    // Todo:
    // 查找当前节点中第一个大于target的key，并返回key的位置给上层
    // 提示: 可以采用多种查找方式：顺序遍历、二分查找等；使用ix_compare()函数进行比较

    // 获取键的数量
    int l = 1, r = this->page_hdr->num_key;

    // 二分查找
    while (l < r) {
        int mid = (l + r) / 2;

        if (ix_compare(get_key(mid), target, file_hdr->col_type, file_hdr->col_len) > 0) {
            r = mid;

        } else {
            l = mid + 1;
        }
    }

    return l;
}

/**
 * @brief 用于叶子结点根据key来查找该结点中的键值对
 * 值value作为传出参数，函数返回是否查找成功
 *
 * @param key 目标key
 * @param[out] value 传出参数，目标key对应的Rid
 * @return 目标key是否存在
 */
bool IxNodeHandle::LeafLookup(const char *key, Rid **value) {
    // Todo:
    // 1. 在叶子节点中获取目标key所在位置
    // 2. 判断目标key是否存在
    // 3. 如果存在，获取key对应的Rid，并赋值给传出参数value
    // 提示：可以调用lower_bound()和get_rid()函数。

    // 1. 在叶子节点中获取目标key所在位置
    int key_pos = lower_bound(key);

    // 2. 判断目标key是否存在
    if (key_pos < GetSize()) {
        // 检查找到的 key 是否与目标 key 匹配
        if (ix_compare(get_key(key_pos), key, file_hdr->col_type, file_hdr->col_len) == 0) {
            // 3. 如果存在，获取 key 对应的 Rid，并赋值给传出参数 value
            *value = get_rid(key_pos);
            return true;  // 返回查找成功
        }
    }

    // 目标 key 不存在
    return false;
}

/**
 * 用于内部结点（非叶子节点）查找目标key所在的孩子结点（子树）
 * @param key 目标key
 * @return page_id_t 目标key所在的孩子节点（子树）的存储页面编号
 */
page_id_t IxNodeHandle::InternalLookup(const char *key) {
    // Todo:
    // 1. 查找当前非叶子节点中目标key所在孩子节点（子树）的位置
    // 2. 获取该孩子节点（子树）所在页面的编号
    // 3. 返回页面编号

    // 1. 查找当前非叶子节点中目标 key 所在孩子节点（子树）的位置
    int child_pos = upper_bound(key) - 1;  // upper_bound返回值从1开始

    // 2. 获取该孩子节点（子树）所在页面的编号
    // 3. 返回页面编号
    return ValueAt(child_pos);
}

/**
 * @brief 在指定位置插入n个连续的键值对
 * 将key的前n位插入到原来keys中的pos位置；将rid的前n位插入到原来rids中的pos位置
 *
 * @param pos 要插入键值对的位置
 * @param (key, rid) 连续键值对的起始地址，也就是第一个键值对，可以通过(key, rid)来获取n个键值对
 * @param n 键值对数量
 * @note [0,pos)           [pos,num_key)
 *                            key_slot
 *                            /      \
 *                           /        \
 *       [0,pos)     [pos,pos+n)   [pos+n,num_key+n)
 *                      key           key_slot
 */
void IxNodeHandle::insert_pairs(int pos, const char *key, const Rid *rid, int n) {
    // Todo:
    // 1. 判断pos的合法性
    // 2. 通过key获取n个连续键值对的key值，并把n个key值插入到pos位置
    // 3. 通过rid获取n个连续键值对的rid值，并把n个rid值插入到pos位置
    // 4. 更新当前节点的键数量

    // 1. 判断 pos 的合法性
    if (pos < 0 || pos > GetSize() || n <= 0) {
        return;
    }

    // 后移原有键值
    for (int i = GetSize() - 1; i >= pos; --i) {
        set_key(i + n, get_key(i));
        set_rid(i + n, *get_rid(i));
    }
    // 2.通过key获取n个连续键值对的key值，并把n个key值插入到pos位置
    for (int i = 0; i < n; ++i) {
        set_key(pos + i, key + i * file_hdr->col_len);  // 迭代获取新的key
                                                        //  3.通过rid获取n个连续键值对的rid值，并把n个rid值插入到pos位置
        set_rid(pos + i, rid[i]);
    }

    // 4. 更新当前节点的键数量
    SetSize(GetSize() + n);
}

/**
 * @brief 用于在结点中的指定位置插入单个键值对
 */
void IxNodeHandle::insert_pair(int pos, const char *key, const Rid &rid) { insert_pairs(pos, key, &rid, 1); };

/**
 * @brief 用于在结点中插入单个键值对。
 * 函数返回插入后的键值对数量
 *
 * @param (key, value) 要插入的键值对
 * @return int 键值对数量
 */
int IxNodeHandle::Insert(const char *key, const Rid &value) {
    // Todo:
    // 1. 查找要插入的键值对应该插入到当前节点的哪个位置
    // 2. 如果key重复则不插入
    // 3. 如果key不重复则插入键值对
    // 4. 返回完成插入操作之后的键值对数量

    // 1. 查找要插入的键值对应该插入到当前节点的哪个位置
    int pos = lower_bound(key);

    // 2. 如果key重复则不插入
    if (ix_compare(get_key(pos), key, file_hdr->col_type, file_hdr->col_len) == 0) {
        return GetSize();  // 返回当前节点的键值对数量，插入失败
    }

    // 3. 如果key不重复则插入键值对
    insert_pair(pos, key, value);

    // 4. 返回完成插入操作之后的键值对数量
    return GetSize();
}

/**
 * @brief 用于在结点中的指定位置删除单个键值对
 *
 * @param pos 要删除键值对的位置
 */
void IxNodeHandle::erase_pair(int pos) {
    // Todo:
    // 1. 删除该位置的key
    // 2. 删除该位置的rid
    // 3. 更新结点的键值对数量

    // 1. 删除该位置的 key
    // 2. 删除该位置的 rid
    for (int i = pos; i < GetSize(); ++i) {
        set_key(i, get_key(i + 1));
        set_rid(i, *get_rid(i + 1));
    }

    // 3. 更新结点的键值对数量
    SetSize(GetSize() - 1);
}

/**
 * @brief 用于在结点中删除指定key的键值对。函数返回删除后的键值对数量
 *
 * @param key 要删除的键值对key值
 * @return 完成删除操作后的键值对数量
 */
int IxNodeHandle::Remove(const char *key) {
    // Todo:
    // 1. 查找要删除键值对的位置
    // 2. 如果要删除的键值对存在，删除键值对
    // 3. 返回完成删除操作后的键值对数量

    // 1. 查找要删除键值对的位置
    int pos = lower_bound(key);

    // 2. 如果要删除的键值对存在，删除键值对
    if (ix_compare(get_key(pos), key, file_hdr->col_type, file_hdr->col_len) == 0) {
        erase_pair(pos);
    }

    // 3. 返回完成删除操作后的键值对数量
    return GetSize();
}

/**
 * @brief 由parent调用，寻找child，返回child在parent中的rid_idx∈[0,page_hdr->num_key)
 *
 * @param child
 * @return int
 */
int IxNodeHandle::find_child(IxNodeHandle *child) {
    int rid_idx;
    for (rid_idx = 0; rid_idx < page_hdr->num_key; rid_idx++) {
        if (get_rid(rid_idx)->page_no == child->GetPageNo()) {
            break;
        }
    }
    assert(rid_idx < page_hdr->num_key);
    return rid_idx;
}

/**
 * @brief used in internal node to remove the last key in root node, and return the last child
 *
 * @return the last child
 */
page_id_t IxNodeHandle::RemoveAndReturnOnlyChild() {
    assert(GetSize() == 1);
    page_id_t child_page_no = ValueAt(0);
    erase_pair(0);
    assert(GetSize() == 0);
    return child_page_no;
}