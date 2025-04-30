#pragma once

#include <JuceHeader.h>
#include <mutex>
#include <functional>

template <typename VecT>
class PlotDataBuffer
{
public:
    explicit PlotDataBuffer(size_t capacity = 2048)
        : capacity(capacity), buffer(capacity) {
    }

    void append(const VecT& point)
    {
        if (threadSafe) std::scoped_lock lock(bufferMutex);

        buffer[writeIndex] = point;
        writeIndex = (writeIndex + 1) % capacity;
        if (writeIndex == 0) wrapped = true;
    }

    void appendBlock(const std::vector<VecT>& points)
    {
        if (threadSafe) std::scoped_lock lock(bufferMutex);

        for (const auto& p : points)
        {
            buffer[writeIndex] = p;
            writeIndex = (writeIndex + 1) % capacity;
            if (writeIndex == 0) wrapped = true;
        }
    }

    void clear()
    {
        if (threadSafe) std::scoped_lock lock(bufferMutex);

        std::fill(buffer.begin(), buffer.end(), VecT());
        writeIndex = 0;
        wrapped = false;
    }

    size_t getSize() const
    {
        return wrapped ? capacity : writeIndex;
    }

    size_t getCapacity() const
    {
        return capacity;
    }

    std::vector<VecT> getCopy() const
    {
        if (threadSafe) std::scoped_lock lock(bufferMutex);

        std::vector<VecT> out(getSize());

        if (!wrapped)
        {
            std::copy(buffer.begin(), buffer.begin() + writeIndex, out.begin());
        }
        else
        {
            size_t tail = capacity - writeIndex;
            std::copy(buffer.begin() + writeIndex, buffer.end(), out.begin());
            std::copy(buffer.begin(), buffer.begin() + writeIndex, out.begin() + tail);
        }

        return out;
    }

    void lockForReading(std::function<void(const VecT* data, size_t size)> callback) const
    {
        if (threadSafe) std::scoped_lock lock(bufferMutex);

        if (!wrapped)
        {
            callback(buffer.data(), writeIndex);
        }
        else
        {
            tempBuffer.resize(capacity);
            size_t tail = capacity - writeIndex;
            std::copy(buffer.begin() + writeIndex, buffer.end(), tempBuffer.begin());
            std::copy(buffer.begin(), buffer.begin() + writeIndex, tempBuffer.begin() + tail);
            callback(tempBuffer.data(), capacity);
        }
    }

    void setThreadSafe(bool enabled)
    {
        threadSafe = enabled;
    }

private:
    std::vector<VecT> buffer;
    mutable std::vector<VecT> tempBuffer;
    mutable std::mutex bufferMutex;

    size_t capacity;
    size_t writeIndex = 0;
    bool wrapped = false;
    bool threadSafe = true;
};


// === Type Aliases for Common Plot Buffer Types ===

using PlotDataBuffer2D = PlotDataBuffer<juce::Point<float>>;
using PlotDataBuffer3D = PlotDataBuffer<juce::Vector3D<float>>;
