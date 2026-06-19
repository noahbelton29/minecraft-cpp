#include "minecraft/minecraft.h"

int main() {
  Minecraft::Minecraft minecraft(
      WINDOW_WIDTH, WINDOW_HEIGHT, "Minecraft", Minecraft::RendererAPI::OpenGL);
  minecraft.run();
  return 0;
}
