#ifndef CAMERA_HPP
#define CAMERA_HPP


#include "Prereqs.hpp"

#include <linux/videodev2.h>
#include <string>
#include <utility>


class Camera
{
public:
    Camera();
    ~Camera();

    void setFileName(const std::string& fileName);
    const std::string& fileName() const;

    void setCaptureSize(unsigned int width, unsigned int height);
    std::pair<unsigned int, unsigned int> captureSize() const;

    __u32 pixelFormat() const;
    std::string pixelFormatString() const;
    enum v4l2_field fieldFormat() const;
    unsigned int bufferSize() const;

    void setReadTimeOut(unsigned int seconds);
    unsigned int readTimeOut() const;

    void init();
    void finish();

    void printDeviceInfo() const;
    void printControls() const;
    void printFormats() const;

    unsigned char *lockBufferForWriting();
    unsigned char *lockBufferForReading();
    void unlockBuffer(unsigned char *buffer);

private:

    /** @returns wether the id was a valid one */
    bool  queryControl(__u32 id) const;
    /** helper, which calls ioctl until an undisturbed call has been done */
    static int xioctl(int fileDescriptor, int request, void *arg);

    std::string m_fileName;
    int m_fileDescriptor;
    unsigned int m_height;
    unsigned int m_width;
    __u32 m_pixelFormat;
    enum v4l2_field m_fieldFormat;
    unsigned int m_readTimeOut;

    unsigned char *m_bufferOne;
    unsigned char *m_bufferTwo;
    unsigned int m_bufferSize;
};


#endif /* CAMERA_HPP */
