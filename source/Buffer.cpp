#include "Buffer.h"

#include <stdexcept>
#include <cstring>

namespace rp::curtis
{
    Buffer::Buffer()
    : data_(nullptr)
    , size_(0)
    , capacity_(0)
    , owned_(false)
    {
    }

    Buffer::Buffer(size_t capacity)
    : size_(0)
    , capacity_(capacity)
    , owned_(true)
    {
        data_ = static_cast<float*>(malloc(sizeof(float) * size_));
    }

    Buffer::Buffer(float* buffer, size_t size)
    : data_(buffer)
    , size_(size)
    , capacity_(size_)
    , owned_(false)
    {
    }

    Buffer::~Buffer()
    {
        if(owned_)
            free(data_);
    }

    void Buffer::copyFrom(const IBuffer& buffer)
    {
        if(owned_)
            free(data_);

        data_ = static_cast<float*>(malloc(buffer.size() * sizeof(float)));
        size_ = buffer.size();
    }

    size_t Buffer::size() const
    {
        return size_;
    }

    const float* Buffer::getReadPtr() const
    {
        return data_;
    }

    float* Buffer::getWritePtr()
    {
        return data_;
    }

    bool Buffer::owned() const
    {
        return owned_;
    }

    void Buffer::clear()
    {
        size_ = 0;
    }

    void Buffer::append(const IBuffer& buffer)
    {
        if(size_ + buffer.size() > capacity_)
            throw std::out_of_range("appended buffer is to big");

        memcpy(data_ + size_, buffer.getReadPtr(), buffer.size() * sizeof(float));
        size_ += buffer.size();
    }

    void Buffer::push(float value)
    {
        if(size_ >= capacity_)
            throw std::out_of_range("cannot push more value");

        data_[size_] = value;
        size_++;
    }

    float Buffer::getLast() const
    {
        if( size_ == 0)
            return 0.0f;

        return data_[size_ - 1];
    }




}
