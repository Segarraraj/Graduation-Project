#include "renderer/entity.h"

#include "renderer/common.hpp"
#include "renderer/components/entity_component.h"
#include "renderer/components/local_transform_component.h"
#include "renderer/components/world_transform_component.h"

RR::Entity::Entity(uint32_t components) { 
  for (uint32_t i = 1; i < components; i = (i << 1)) {
    if ((components & i) != i) {
      continue;
    }

    switch (i) {
      case RR::kComponentType_WorldTransform:
        _components[i] = std::make_shared<WorldTransform>();
        break;
      case RR::kComponentType_LocalTransform:
        _components[i] = std::make_shared<LocalTransform>();
        break;
      case RR::kComponentType_Renderer:
        break;
      case RR::kComponentType_Camera:
        break;
    }
  }
}

std::shared_ptr<RR::EntityComponent> RR::Entity::GetComponent(uint32_t component_type) {
  return _components[component_type];
}
