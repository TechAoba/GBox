#pragma once

namespace GBox
{

class TimeStep {
public:
    TimeStep(float time = 0.0f) : m_Time(time) {
        
    }

    // can be used to calculate times operator: a * timestep
    operator float() const { return m_Time; }

    float GetSeconds() const { return m_Time; }
    float GetMilliseconds() const { return m_Time * 1000.0f; }
private:
    float m_Time;
};

} // namespace GBox
