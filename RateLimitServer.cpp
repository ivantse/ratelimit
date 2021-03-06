#include <memory>

#include "pipeline/RedisPipelineBootstrap.h"
#include "ratelimit/RateLimitHandler.h"

namespace ratelimit {

static pipeline::RedisPipelineBootstrap::Config config{
  redisHandlerFactory : [](pipeline::RedisPipelineBootstrap* bootstrap) -> std::shared_ptr<pipeline::RedisHandler> {
    return std::make_shared<RateLimitHandler>(bootstrap->getDatabaseManager());
  },

  kafkaTailerFactoryMap : {},

  databaseManagerFactory : nullptr,

  scheduledTaskProcessorFactoryMap : {},

  rocksDbCfConfiguratorMap : {
      {
          pipeline::DatabaseManager::defaultColumnFamilyName(), RateLimitHandler::optimizeColumnFamily,
      },
  },
};

static auto redisPipelineBootstrap = pipeline::RedisPipelineBootstrap::create(config);

}  // namespace ratelimit
