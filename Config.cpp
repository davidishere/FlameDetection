#include "Config.h"
#include "qdir.h"

CConfig::CConfig()
{
    LoadXmlFile();
}

void CConfig::LoadXmlFile()
{
    if (!QDir(CONF_PATH).exists())
        QDir().mkdir(CONF_PATH);


    CvFileStorage* fs = NULL;

    try
    {
        fs = cvOpenFileStorage(XML_FILE, 0, CV_STORAGE_READ);
    }
    catch (...)
    {
        setDefault();
        return;
    }


    if (fs == NULL)
    {
        setDefault();
        return;
    }

    _config.strCamUrl        = cvReadStringByName(fs, 0, "CamUrl", "rtsp://192.168.0.253:554/stream1");
    _config.frmPosX          = cvReadIntByName(fs, 0, "FrmPosX", 0);
    _config.frmPosY          = cvReadIntByName(fs, 0, "FrmPosY", 0);
    _config.frmWidth         = cvReadIntByName(fs, 0, "FrmWidth", 800);
    _config.frmHeight        = cvReadIntByName(fs, 0, "FrmHeight", 600);
    _config.smallArea        = cvReadIntByName(fs, 0, "SmallArea", 50);
    _config.largeArea        = cvReadIntByName(fs, 0, "LargeArea", 300);
    _config.keepCount        = cvReadIntByName(fs, 0, "KeepCount", 2);
    _config.movDetect        = cvReadRealByName(fs, 0, "MovDetect", -1);
    _config.brightThreshold  = cvReadIntByName(fs, 0, "BrightThreshold", 235);

    cvReleaseFileStorage(&fs);
}

void CConfig::setDefault()
{
    _config.strCamUrl       = "rtsp://192.168.0.253:554/stream1";
    _config.frmPosX         = 0;
    _config.frmPosY         = 0;
    _config.frmWidth        = 800;
    _config.frmHeight       = 600;
    _config.smallArea       = 50;
    _config.largeArea       = 300;
    _config.keepCount       = 2;
    _config.movDetect       = -1;
    _config.brightThreshold = 235;
    SaveXmlFile();
}



void CConfig::SaveXmlFile()
{
    CvFileStorage* fs = cvOpenFileStorage(XML_FILE, 0, CV_STORAGE_WRITE);

    cvWriteString(fs, "CamUrl", _config.strCamUrl.data());
    cvWriteInt(fs, "FrmPosX", _config.frmPosX);
    cvWriteInt(fs, "FrmPosY", _config.frmPosY);
    cvWriteInt(fs, "FrmWidth", _config.frmWidth);
    cvWriteInt(fs, "FrmHeight", _config.frmHeight);    
    cvWriteInt(fs, "SmallArea", _config.smallArea);
    cvWriteInt(fs, "LargeArea", _config.largeArea);
    cvWriteInt(fs, "KeepCount", _config.keepCount);
    cvWriteReal(fs, "MovDetect", _config.movDetect);
    cvWriteInt(fs, "BrightThreshold", _config.brightThreshold);

    cvReleaseFileStorage(&fs);
}
