#ifndef LIBRAWDATAPROVIDER_H
#define LIBRAWDATAPROVIDER_H

//General includes
#include <memory>

//OpenCineAPI includes
#include "../API/IDataProvider.h"

//LibRaw includes
#include <libraw/libraw.h>

using namespace OpenCineAPI;

class LibRawDataProvider : public IDataProvider
{
    LibRaw* imageProcessor;

public:
    LibRawDataProvider();
    ~LibRawDataProvider();

    // IDataProvider interface
    OCImage* LoadFile(std::string filePath);
    OCImage* LoadFolder(std::string folderPath);

    // IPlugin interface
    std::string GetName();
};

#endif //LIBRAWDATAPROVIDER_H
