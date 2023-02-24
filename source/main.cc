#include "renderer/renderer.h"

#include "renderer/entity.h"
#include "renderer/components/entity_component.h"
#include "renderer/components/local_transform_component.h"
#include "renderer/common.hpp"

static struct UserData {
  RR::Renderer* renderer;
  std::shared_ptr<RR::Entity> cube1;
  std::shared_ptr<RR::Entity> cube2;
};

static void update(void* user_data) { 
  UserData* data;
}

int main(int argc, char** argv) {
  RR::Renderer renderer;
  UserData data = {};

  int result = renderer.Init((void*) &data, update);
  if (result != 0) {
    return 1;
  }

  data.renderer = &renderer;
  data.cube1 = renderer.RegisterEntity(0);
  data.cube2 = renderer.RegisterEntity(0);

  std::shared_ptr<RR::LocalTransform> transform =
      std::static_pointer_cast<RR::LocalTransform>(
          data.cube2->GetComponent(RR::kComponentType_LocalTransform));

  transform->scale = {.25f, .25f, .25f};
  transform->position = {5.f, .0f, .0f};
  transform->SetParent(data.cube1);

  transform = std::static_pointer_cast<RR::LocalTransform>(
      data.cube1->GetComponent(RR::kComponentType_LocalTransform));

  transform->scale = {.5f, .5f, .5f};

  transform = std::static_pointer_cast<RR::LocalTransform>(
      renderer.MainCamera()->GetComponent(RR::kComponentType_LocalTransform));;
  transform->position = {.0f, 1.5f, -6.0f};
  transform->rotation = {15.0f, 180.0f, .0f};

  // Create vertex buffer
  float vertex_list[] = {
      // front face
      -1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
      1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 1.0f,
      -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
      1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,

      // right side face
      1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
      1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
      1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
      1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,

      // left side face
      -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
      -1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 1.0f,
      -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
      -1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,

      // back face
      1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
      -1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
      1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
      -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

      // top face
      -1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
      1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
      1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
      -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

      // bottom face
      1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
      -1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 1.0f,
      1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
      -1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
  };

  uint32_t indices[] = {
      // ffront face
      0, 1, 2,  // first triangle
      0, 3, 1,  // second triangle

      // left face
      4, 5, 6,  // first triangle
      4, 7, 5,  // second triangle

      // right face
      8, 9, 10,  // first triangle
      8, 11, 9,  // second triangle

      // back face
      12, 13, 14,  // first triangle
      12, 15, 13,  // second triangle

      // top face
      16, 17, 18,  // first triangle
      16, 19, 17,  // second triangle

      // bottom face
      20, 21, 22,  // first triangle
      20, 23, 21,  // second triangle
  };

  std::shared_ptr<RR::GeometryData> gdata = std::make_shared<RR::GeometryData>();
  gdata->vertex_data = vertex_list; 
  gdata->index_data = indices;
  gdata->vertex_size = sizeof(vertex_list);
  gdata->index_size = sizeof(indices);

  renderer.CreateGeometry(RR::GeometryTypes::kGeometryType_Positions_Normals,
                          gdata);

  renderer.Start();

  return 0;
}