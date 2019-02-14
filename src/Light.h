#include <glm/glm.hpp>

class Light {
    private:
        const float *scaleColorChannels;
        glm::vec3 color;
        glm::vec3 position;
        bool activeColorChannels[3];
        bool grayscaleActive;
        bool active;
    public:
        const enum CHANNELS {R, G, B};
        const static float DEFAULT_LIGHT_SCALE[3];
        const static float GRAYSCALE_LIGHT_SCALE[3];
        Light(glm::vec3 color, glm::vec3 position);
        glm::vec3 getColor();
        glm::vec3 getPosition();
        void toggleChannel(Light::CHANNELS channel);
        void toggleChannel(Light::CHANNELS channel, bool state);
        void toggle();
        void toggleGrayscale();
};