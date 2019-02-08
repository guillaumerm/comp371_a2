#include <glm/glm.hpp>

class Object{
    private:
        glm::vec3 position;
        glm::vec3 scale;
        float pitch = 0.0f;
        float yaw = 0.0f;
        float roll = 0.0f;
    public:
        Object(); 
        glm::vec3 getPosition() const;
        glm::vec3 getScale() const;
        void setScale(glm::vec3 scale);
        void translate(glm::vec3 displacement);
        float getPitch() const;
        float getYaw() const;
        float getRoll() const;
        void setPitch(float degree);
        void setYaw(float degree);
        void setRoll(float degree);
        void reset();
        ~Object();
};