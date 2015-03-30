#include "RawSpeedDataProvider.h"

using namespace std;


int rawspeed_get_number_of_processor_cores()
{
  return 1;
}

//LibRaw includes
//#include "RawSpeed/RawSpeed-API.h"

//using namespace RawSpeed;

//static CameraMetaData *metadata = NULL;

RawSpeedDataProvider::RawSpeedDataProvider() : IDataProvider("RawSpeedDataProvider")
{    
//    if (NULL == metadata)
//    {
//        try
//        {
//            metadata = new CameraMetaData("/home/andi/Source/OpenCine/3rdParty/RawSpeed/data/cameras.xml");
//        }
//        catch (CameraMetadataException &e)
//        {
//            // Reading metadata failed. e.what() will contain error message.
//        }
//    }
}

RawSpeedDataProvider::~RawSpeedDataProvider()
{

}

//#include <locale>
//#include <codecvt>
#include <string>

//std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

OCFrame* RawSpeedDataProvider::LoadFile(std::string filePath)
{
    OCFrame* image = new OCFrame();

    //std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    //converter.from_bytes(filePath)
    //wstring t(filePath.c_str());
    //FileReader reader(t);
    //FileMap* map = NULL;
//    try
//    {
//      map = reader.readFile();
//    }
//    catch (FileIOException &e)
//    {
//      // Handle errors
//    }

    // Creation of image processing object
    //imageProcessor->open_file(filePath.c_str());
    //imageProcessor->unpack();
    //imageProcessor.dcraw_process();
    //libraw_processed_image_t* rawImage = imageProcessor.dcraw_make_mem_image();

    //image->SetSize(rawImage->width, rawImage->height);
    //image->SetData(rawImage->data, rawImage->data_size);

    //image->SetSize(imageProcessor->imgdata.rawdata.sizes.width, imageProcessor->imgdata.rawdata.sizes.height);
    //image->SetData(imageProcessor->imgdata.rawdata.raw_image, imageProcessor->imgdata.rawdata.sizes.raw_pitch * imageProcessor->imgdata.rawdata.sizes.height);

    //imageProcessor.dcraw_clear_mem(rawImage);

    return image;
}

OCFrame* RawSpeedDataProvider::LoadFolder(std::string folderPath)
{
    return nullptr;
}

std::string RawSpeedDataProvider::GetName()
{
    return "RawSpeedDataProvider";
}
