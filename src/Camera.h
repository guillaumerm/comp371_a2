#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera{
    private:
        glm::vec3 position;
        glm::vec3 front;
        glm::vec3 up;
        float fov;
        float speed;
    public:
        Camera();
        //! Caculates the right vector. That is the result of the cross product between FRONT and and UP vectors. 
        glm::vec3 right() const;

        //! Yaw (rotate upon the UP vector) the camera at a certain angle from its current orientation
        /*!
        \param angle Angle, expressed in degrees, at which the camera will be yawed.
        */
        void yaw(float degree);

        //! Pitch (rotate upon the RIGHT vector) the camera at a certain angle from its current orientation.
        /*!
        \param angle Angle, expressed in degrees, at which the camera will be pitched.
        */
        void pitch(float degree);

        void moveForward();

        void moveBackward();

        void moveRight();

        void moveLeft();

        glm::vec3 getPosition() const;

        glm::vec3 getFront() const;

        glm::vec3 getUp() const;

        float getFov() const;

        void reset();
        ~Camera();
};