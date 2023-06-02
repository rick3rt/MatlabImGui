#ifndef DEMO_HPP_
#define DEMO_HPP_

#include "App.hpp"

// =============================================================================
// Demo class
// =============================================================================
class Demo : public App
{

  public:
    using App::App;

    ~Demo() {}

    // will run during initialization
    void Start() override;

    // display loop
    void Update() override;
};

#endif //! DEMO_HPP_