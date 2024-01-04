#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <Ray.hpp>
const float YAW         = -89.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;
class Camera
{
public:
    enum Camera_Movement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };
public:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    float Yaw;
    float Pitch;
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
    float Near = 0.1f;
    float Far = 100.0f;
    int width;
    int height;

    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    void setWidth(int val)
    {
        width = val;
    }

    void setHeight(int val)
    {
        height = val;
    }

    std::vector<TE::Math::TVector<double>> ScreenPosToWorldPos(float mouse_x, float mouse_y, int width,int height)
    {
        float ndc_x = (2.0f * mouse_x) / width - 1.0f;
        float ndc_y = 1.0-(2.0f * mouse_y) / height;
        float ndc_z = -1.0;
        glm::vec3 ray_nds(ndc_x, ndc_y, ndc_z);
        glm::vec4 origin(ray_nds, 1.0);
        glm::vec4 target(ray_nds, 1.0);
        origin.z = -1.0;
        target.z = 1.0;
        glm::mat4 InvProjectViewMatrix = glm::inverse(GetProjectionMatrix(width, height) * GetViewMatrix());
        origin = InvProjectViewMatrix*origin;
        target = InvProjectViewMatrix*target;
        if (origin.w != 0) {
            origin/= origin.w;
        }
        if (target.w != 0) {
            target /= target.w;
        }
        return std::vector<TE::Math::TVector<double>>{TE::Math::TVector<double>(origin.x, origin.y, origin.z), TE::Math::TVector<double>(target.x, target.y, target.z)};
    }

    TE::Math::TRay<double>CreateRay(float mouse_x, float mouse_y, int width, int height)
    {
        auto wpos = ScreenPosToWorldPos(mouse_x, mouse_y, width, height);
        auto direction = wpos[1] - wpos[0];
        direction.Normalize();
        return TE::Math::TRay<double>(wpos[0],direction);
    }

    glm::mat4 GetProjectionMatrix(int width, int height)
    {
		return glm::perspective(glm::radians(Zoom), (float)width / (float)height, Near, Far);
    }

    glm::mat4 GetProjectionMatrix()
    {
        return GetProjectionMatrix(width, height);
    }

    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        float velocity = MovementSpeed * deltaTime;
        if (direction == FORWARD)
            Position += Front * velocity;
        if (direction == BACKWARD)
            Position -= Front * velocity;
        if (direction == LEFT)
            Position -= Right * velocity;
        if (direction == RIGHT)
            Position += Right * velocity;
    }

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true)
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw   += xoffset;
        Pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        // update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();
    }

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset)
    {
        Zoom -= (float)yoffset;
        if (Zoom < 1.0f)
            Zoom = 1.0f;
        if (Zoom > 45.0f)
            Zoom = 45.0f;
    }

private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors()
    {
        // calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
        // also re-calculate the Right and Up vector
        Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up    = glm::normalize(glm::cross(Right, Front));
    }
};
#endif
