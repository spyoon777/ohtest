// Copyright(c) 2022 KOREA ELECTRONICS TECHNOLOGY INSTITUTE(KETI), All Rights Reserved.
// Author: spyoon777

#include <iostream>
#include <string>
#include <filesystem>

#include "ophPointCloud.h"

#include "config/config.h"

namespace fs = std::filesystem;

int main() {
    // Create ophPointCloud instance
    ophPointCloud* Hologram = new ophPointCloud();

    // Read Config Parameters for Point Cloud CGH
    std::string proj_dir = PROJ_PATH;
    std::string conf_file = proj_dir + "/oht/config/PointCloud.xml";
    Hologram->readConfig(conf_file.c_str());

    // Load Point Cloud Data(*.PLY)
    std::string pc_file = proj_dir + "/dataset/pointcloud/dice_100000.ply";
    Hologram->loadPointCloud(pc_file.c_str());

    // Select CPU or GPU Processing
    Hologram->setMode(MODE_GPU);

    // Select R-S diffraction or Fresnel diffraction
    Hologram->generateHologram(ophPointCloud::PC_DIFF_FLAG::PC_DIFF_RS);

    // Save to ohc(Openholo complex field file format)
    std::string res_path = "./result/pointcloud/";
    if (!fs::exists(res_path)) {
        fs::create_directories(res_path);
    }
    Hologram->saveAsOhc(std::string(res_path + "pc_sample.ohc").c_str());

    // Encode Complex Field to Real Field
    Hologram->encoding(Hologram->ENCODE_PHASE);

    // Normalize Real Field to unsigned char(0~255) for save to image(*.BMP)
    Hologram->normalize();

    // Save to bmp
    Hologram->save(std::string(res_path + "pc_sample.bmp").c_str());

    // Release memory used to Generate Point Cloud
    Hologram->release();

    return 0;
}
