#include "M2Extractor.h"

#include "../GlobalData.h"
#include "../Utils/ServiceLocator.h"
#include "../Utils/JobBatchRunner.h"
#include "../Utils/MPQLoader.h"
#include "../Formats/M2/M2.h"

#include <filesystem>
namespace fs = std::filesystem;

void M2Extractor::ExtractM2s(std::shared_ptr<JobBatchRunner> jobBatchRunner)
{
    auto& globalData = ServiceLocator::GetGlobalData();

    json& m2Config = globalData->config.GetJsonObjectByKey("M2");
    if (m2Config["Extract"] == false)
        return;

    std::shared_ptr<MPQLoader> mpqLoader = ServiceLocator::GetMPQLoader();

    JobBatch m2JobBatch;
    mpqLoader->GetFiles("*.m2", [&](char* fileName, size_t fileNameLength)
    {
        std::string fileNameStr = fileName;
        std::string name = std::string(fileName, fileNameLength - 3) + ".nm2";

        fs::path outputPath = (globalData->nm2Path / name).make_preferred();

        // Create Directories for file
        fs::create_directories(outputPath.parent_path());

        m2JobBatch.AddJob(0, [this, fileNameStr, outputPath]()
        {
            M2File modelFile;
            if (modelFile.GetFromMPQ(fileNameStr))
            {
                modelFile.SaveToDisk(outputPath);
            }
        });
    });

    NC_LOG_MESSAGE("Adding M2 batch of %u jobs", m2JobBatch.GetJobCount());

    JobBatchToken mainBatchToken = jobBatchRunner->AddBatch(m2JobBatch);
    mainBatchToken.WaitUntilFinished();
}
