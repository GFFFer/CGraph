/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: CStatus.h
@Time: 2021/12/17 10:32 下午
@Desc: 命名为 CSTATUS，直接对外提供的是 CStatus 类
***************************/

#ifndef CGRAPH_CSTATUS_H
#define CGRAPH_CSTATUS_H

#include <string>

#include "CObjectDefine.h"

CGRAPH_NAMESPACE_BEGIN

static const char* STATUS_ERROR_INFO_CONNECTOR = " && ";

class CSTATUS {
public:
    explicit CSTATUS() = default;

    explicit CSTATUS(const std::string &errorInfo) {
        this->error_code_ = STATUS_ERR;    // 默认的error code信息
        this->error_info_ = errorInfo;
    }

    explicit CSTATUS(int errorCode, const std::string &errorInfo) {
        this->error_code_ = errorCode;
        this->error_info_ = errorInfo;
    }

    CSTATUS(const CSTATUS &status) {
        this->error_code_ = status.error_code_;
        this->error_info_ = status.error_info_;
    }

    CSTATUS(const CSTATUS &&status) noexcept {
        this->error_code_ = status.error_code_;
        this->error_info_ = status.error_info_;
    }

    CSTATUS& operator=(const CSTATUS& status) = default;

    void operator+=(const CSTATUS& cur) {
        if (this->isOK() && cur.isOK()) {
            return;
        }

        error_info_ = this->isOK()
                ? cur.error_info_
                : (cur.isOK()
                    ? error_info_
                    : (error_info_ + STATUS_ERROR_INFO_CONNECTOR + cur.error_info_));
        error_code_ = STATUS_ERR;
    }

    [[nodiscard]] int getCode() const {
        return this->error_code_;
    }

    [[nodiscard]] const std::string& getInfo() const {
        return this->error_info_;
    }

    /**
     * 判断当前状态是否可行
     * @return
     */
    [[nodiscard]] bool isOK() const {
        return STATUS_OK == error_code_;
    }

private:
    int error_code_ { STATUS_OK };                   // 错误码信息
    std::string error_info_;                         // 错误信息描述
};

CGRAPH_NAMESPACE_END

using CStatus = CGraph::CSTATUS;                     // 方便外部直接使用

#endif //CGRAPH_CSTATUS_H
