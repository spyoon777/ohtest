// Copyright(c) 2022 KOREA ELECTRONICS TECHNOLOGY INSTITUTE(KETI), All Rights Reserved.
// Author: spyoon777

#include <iostream>
#include <string>
#include <filesystem>

#include "ophPointCloud.h"
#include "ophDepthMap.h"

#include "config/config.h"

namespace fs = std::experimental::filesystem;

int main() {
    //// Point Cloud Example

    // Create ophPointCloud instance
    ophPointCloud* Hologram = new ophPointCloud();

    std::string proj_dir = PROJ_PATH;
    std::string conf_file = proj_dir + "/oht/config/Dice_PointCloud.xml";

    // Read Config Parameters for Point Cloud CGH
    if (!Hologram->readConfig(conf_file.c_str())) {
        std::cerr << "Config file load failed" << std::endl;
        exit(1);
    }

    // Load Point Cloud Data(*.PLY)
    std::string pc_file = proj_dir + "/dataset/pointcloud/dice_100000.ply";
    if (Hologram->loadPointCloud(pc_file.c_str()) < 0) {
        std::cerr << "Pointcloud file load failed" << std::endl;
        exit(1);
    }

    // Select CPU or GPU Processing
    // param = MODE_CPU or MODE_GPU
    Hologram->SetMode(MODE_GPU);

    // Select R-S diffraction or Fresnel diffraction
    Hologram->generateHologram(ophPointCloud::PC_DIFF_FLAG::PC_DIFF_RS);

    // Save to ohc(Openholo complex field file format)
    std::string res_path = "./result/pointcloud/";
    if (!fs::exists(res_path)) {
        fs::create_directories(res_path);
    }
    if (!Hologram->saveAsOhc(std::string(res_path + "pc_sample.ohc").c_str())) {
        std::cerr << "OHC file save failed" << std::endl;
        exit(1);
    }

    // Encode Complex Field to Real Field
    Hologram->encoding(Hologram->ENCODE_PHASE);

    // Normalize Real Field to unsigned char(0~255) for save to image(*.BMP)
    Hologram->normalize();

    // Save to bmp
    if (!Hologram->save(std::string(res_path + "pc_sample.bmp").c_str())) {
        std::cerr << "BMP file save failed" << std::endl;
        exit(1);
    }

    // Release memory used to Generate Point Cloud
    Hologram->release();

    return 0;
}
