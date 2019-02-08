#include "Object.h"

Object::Object() {
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f); /*!< Position of the object */
    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f); /*!< Current scale of the object */
    float pitch = 0.0f; /*!< Current pitch of the object */
    float yaw = 0.0f; /*!< Current yuw of the object */
    float roll = 0.0f; /*!< Current roll of the object */
}

void Object::translate(glm::vec3 displacement) {
    this->position += displacement;
}

void Object::setScale(glm::vec3 scale){
    this->scale = scale;
}

float Object::getPitch() const {
    return this->pitch;
}

float Object::getYaw() const {
    return this->pitch;
}

float Object::getRoll() const {
    return this->pitch;
}

glm::vec3 Object::getPosition() const {
    return this->position;
}

glm::vec3 Object::getScale() const {
    return this->scale;
}

void Object::setPitch(float degree) {
    this->pitch = degree;
}

void Object::setRoll(float degree) {
    this->roll = degree;
}

void Object::setYaw(float degree) {
    this->yaw = degree;
}

//! Reset the object to its initial configurations.
void Object::reset() {
	this->position = glm::vec3(0.0f, 0.0f, 0.0f);
	this->scale = glm::vec3(1.0f, 1.0f, 1.0f);
	this->pitch = 0.0f;
    this->yaw = 0.0f;
	this->roll = 0.0f;
}

Object::~Object() {

}