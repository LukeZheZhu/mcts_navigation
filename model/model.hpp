#ifndef MODEL_HPP
#define MODEL_HPP

namespace nsModel {
    struct sModelCoordinate {
        float x;
        float y;
        float z;

        sModelCoordinate() :
            x(0.0),
            y(0.0),
            z(0.0) {
        };

        sModelCoordinate(float coordX, float coordY, float height = 0.0) :
            x(coordX),
            y(coordY),
            z(height) {
        };
    }; //struct sModelCoordinate

    struct sModelPose {
    };

    class cModelBase {
        struct sModelPose {
        struct sModelCoordinate m_position;
        float m_direction;
        
    }; //class CModelBase

} // namespace model
#endif //MODEL_HPP
