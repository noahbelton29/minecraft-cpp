#pragma once

#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

namespace Minecraft {
  /**
   * @brief Static input interface wrapping GLFW keyboard, mouse, and gamepad
   * state.
   *
   * Call init() once after the window is created, then update() once per
   * frame before reading any input so deltas and gamepad state are fresh.
   */
  class Input {
  public:
    /**
     * @brief Binds the input system to a window and captures the cursor.
     * @param window The GLFW window to read keyboard and mouse input from.
     */
    static void init(GLFWwindow *window);

    /**
     * @brief Samples mouse position and gamepad state for this frame.
     * Call once per frame before reading any input.
     */
    static void update();

    /**
     * @brief Returns true while the given key is held down.
     * @param key A GLFW_KEY_* constant.
     */
    [[nodiscard]] static bool isKeyDown(int key);

    /**
     * @brief Returns the mouse movement since the last update() call.
     */
    [[nodiscard]] static glm::vec2 mouseDelta();

    /**
     * @brief Returns true if a gamepad is connected and being used.
     */
    [[nodiscard]] static bool gamepadConnected();

    /**
     * @brief Returns the left stick axis as a [-1, 1] vector (X = left/right, Y
     * = forward/back). Dead zone is applied internally.
     */
    [[nodiscard]] static glm::vec2 gamepadLeftStick();

    /**
     * @brief Returns the right stick axis as a [-1, 1] vector (X = yaw, Y =
     * pitch). Dead zone is applied internally.
     */
    [[nodiscard]] static glm::vec2 gamepadRightStick();

    /**
     * @brief Returns true while the given gamepad button is held.
     * @param button A GLFW_GAMEPAD_BUTTON_* constant.
     */
    [[nodiscard]] static bool isGamepadButtonDown(int button);

    /**
     * @brief Returns the name of the connected gamepad for debugging.
     */
    [[nodiscard]] static const char *getGamepadName();

  private:
    static float
    applyDeadZone(float value,
                  float deadZone); // squashes small stick drift to zero

    static GLFWwindow *window_;
    static glm::vec2   lastMousePos_;
    static glm::vec2   mouseDelta_;
    static bool        firstUpdate_;

    static bool             gamepadConnected_;
    static GLFWgamepadstate gamepadState_;
    static int              connectedJoystickId_;

    static constexpr float kDeadZone = 0.15f; // ignore stick values below this
  };
} // namespace Minecraft
