#include "Buffer.h"

#include <stdexcept>
#include <cstring>

namespace rp::curtis
{
    Buffer::Buffer()
    : buffer_(nullptr)
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
        buffer_ = static_cast<float*>(malloc(sizeof(float) * size_));
    }

    Buffer::Buffer(float* buffer, size_t size)
    : buffer_(buffer)
    , size_(size)
    , capacity_(size_)
    , owned_(false)
    {
    }

    Buffer::~Buffer()
    {
        if(owned_)
            free(buffer_);
    }

    void Buffer::copyFrom(const IBuffer& buffer)
    {
        if(owned_)
            free(buffer_);

        buffer_ = static_cast<float*>(malloc(buffer.size() * sizeof(float)));
        size_ = buffer.size();
    }

    size_t Buffer::size() const
    {
        return size_;
    }

    const float* Buffer::get() const
    {
        return buffer_;
    }

    bool Buffer::owned() const
    {
        return owned_;
    }

    void Buffer::clean()
    {
        size_ = 0;
    }

    void Buffer::append(const IBuffer& buffer)
    {
        if(size_ + buffer.size() > capacity_)
            throw std::out_of_range("appended buffer is to big");

        memcpy(buffer_ + size_, buffer.get(), buffer.size() * sizeof(float));
        size_ += buffer.size();
    }

    void Buffer::push(float value)
    {
        if(size_ >= capacity_)
            throw std::out_of_range("cannot push more value");

        buffer_[size_] = value;
        size_++;
    }

    float Buffer::getLast() const
    {
        if( size_ == 0)
            return 0.0f;

        return buffer_[size_-1];
    }


}
