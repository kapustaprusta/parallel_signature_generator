#pragma once

#include <memory>

#include "../task.h"
#include "../../reader/reader.h"
#include "../../writer/writer.h"
#include "../../hash_calculator/hash_calculator.h"

namespace task
{

    class HashTask final : public ITask
    {
        public:
            explicit HashTask(const std::shared_ptr<reader::IReader>& p_reader, const std::shared_ptr<writer::IWRiter>& p_writer);
            ~HashTask() final = default;

            void Start() override;
            void Stop() override;

        private:
            std::shared_ptr<reader::IReader> p_reader_;
            std::shared_ptr<writer::IWRiter> p_writer_;
            std::unique_ptr<hash::IHashCalculator> p_hash_calculator_;
    };

} // task