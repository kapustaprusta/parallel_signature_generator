#pragma once

#include <memory>

#include "../task.h"
#include "../../writer/writer.h"
#include "../../data_structures/shared_queue/shared_queue.h"

namespace task
{

    class WriterTask final : public ITask
    {
        public:
            explicit WriterTask(const std::shared_ptr<writer::IWRiter>& p_writer, const data_structures::SharedQueuePtr& p_shared_queue);
            ~WriterTask() final = default;

            void Start() override;
            void Stop() override;

        private:
            std::shared_ptr<writer::IWRiter> p_writer_;
            data_structures::SharedQueuePtr p_shared_queue_;
    };

} // task