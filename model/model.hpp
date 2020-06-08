#ifndef MODEL_HPP
#define MODEL_HPP

#include <iostream>
#include <cmath>
#include <memory>

#define MODEL_HEIGHT 0.0
#define MODEL_SPEED  1.0
#define MODEL_RADIUS 1.0

namespace nsModel {
    struct sModelCoordinate {
    public:
        float x;
        float y;
        float z;

        sModelCoordinate() :
            x(0.0),
            y(0.0),
            z(0.0) {
        };

        sModelCoordinate(const sModelCoordinate &coord) :
            x(coord.x),
            y(coord.y),
            z(coord.z) {
        };

        sModelCoordinate(float coordX, float coordY, float height = 0.0) :
            x(coordX),
            y(coordY),
            z(height) {
        };
    }; //struct sModelCoordinate

    struct sModelRotation {
    public:
        float yaw;
        float roll;
        float pitch;

        sModelRotation() :
            yaw(0.0),
            roll(0.0),
            pitch(0.0) {
        };

        sModelRotation(const sModelRotation &rotate) :
            yaw(rotate.yaw),
            roll(rotate.roll),
            pitch(rotate.pitch) {
        };

        sModelRotation(float Yaw, float Roll = 0.0, float Pitch = 0.0) :
            yaw(Yaw),
            roll(Roll),
            pitch(Pitch) {
        };
    }; //struct sModelRotation

    struct sModelPose {
        struct sModelCoordinate position;
        struct sModelRotation rotation;

        sModelPose() :
            position(),
            rotation() {
        };

        sModelPose(const sModelPose &pose) :
            position(pose.position),
            rotation(pose.rotation) {
        };

        sModelPose(float coordX, float coordY, float height = 0.0,
                   float yaw = 0.0, float roll = 0.0, float pitch = 0.0) :
            position(coordX, coordY, height),
            rotation(yaw, roll, pitch) {
        }
    }; //struct sModelPose

    class cModel;

    class cModelBase {
        friend cModel;

    protected:
        struct sModelPose m_pose;
        float m_speed;
        float m_radius;

        cModelBase() :
            m_pose(),
            m_speed(MODEL_SPEED),
            m_radius(MODEL_RADIUS) {
        };

        cModelBase(float coordX, float coordY, float height = 0.0,
                   float yaw = 0.0, float roll = 0.0, float pitch = 0.0,
                   float speed = 1.0, float radius = 1.0) :
            m_pose(coordX, coordY, height, yaw, roll, pitch),
            m_speed(speed),
            m_radius(radius) {
        };

    private:
        virtual float getRadius();
        virtual struct sModelPose getPose();
        virtual struct sModelPose calcMove(int index);

        virtual void showPose();
    }; //class cModelBase

    class cModel{
    public:
        cModel() :
            m_pModelBase() {
        };

        cModel(std::shared_ptr<cModelBase> pModelBase) :
            m_pModelBase(pModelBase) {
        };

        float getRadius() {
            return m_pModelBase->getRadius();
        };

        struct sModelPose getPose() {
            return m_pModelBase->getPose();
        };//To-Do: using template function

        struct sModelPose calcMove(int index) {
            return m_pModelBase->calcMove(index);
        };

        void showPose() {
            m_pModelBase->showPose();
        }

    private:
        std::shared_ptr<cModelBase> m_pModelBase;
    }; //class cMode

    class cModelCar : public cModelBase {
    protected:
        std::vector<float> m_turn;

        cModelCar() :
            cModelBase(),
            m_turn(5) {
        };

        cModelCar(float coordX, float coordY, float height = 0.0,
                  float yaw = 0.0, float roll = 0.0, float pitch = 0.0,
                  float speed =  1.0, float radius = 1.0,
                  std::vector<float> turn = {270, 315, 0, 45, 90}) :
            cModelBase(coordX, coordY, height, yaw, roll, pitch,
                       speed, radius),
            m_turn(turn) {
        };

        float getRadius() {
            return m_radius;
        }

        struct sModelPose getPose() {
            return m_pose;
        };

        struct sModelPose calcMove(int index) {
            m_pose.rotation.yaw = m_turn[index];
            m_pose.position.x += m_speed * cos(m_pose.rotation.yaw);
            m_pose.position.y += m_speed * sin(m_pose.rotation.yaw);

            return m_pose;
        };

        void showPose() {
            std::cout << "PoseInfo: "
                      << ", X: "     << m_pose.position.x
                      << ", Y: "     << m_pose.position.y
                      << ", Z: "     << m_pose.position.z
                      << ", yaw: "   << m_pose.rotation.yaw
                      << ", roll: "  << m_pose.rotation.roll
                      << ", pitch: " << m_pose.rotation.pitch
                      << std::endl;
        };


    }; //class cModelCar



} // namespace model

#endif //MODEL_HPP
