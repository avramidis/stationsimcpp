//---------------------------------------------------------------------------//
// Copyright (c) 2020 Eleftherios Avramidis <ea461@cam.ac.uk>
// Research Computing Services, University of Cambridge, UK
//
// Distributed under The MIT License (MIT)
// See accompanying file LICENSE
//---------------------------------------------------------------------------//

#include "ModelPlotting.hpp"
#include "Agent.hpp"
#include "Model.hpp"
#include "cxxplot.hpp"

namespace station_sim {
    void ModelPlotting::plot_agents_locations(const station_sim::Model &model) {
        std::vector<float> x_int;
        std::vector<float> y_int;

        for (const auto &agent : model.agents) {
            const Point2D agent_location = agent.get_agent_location();
            x_int.emplace_back(agent_location.x);
            y_int.emplace_back(agent_location.y);
        }

        cxxplot::Kwargs args;
        args.add_kwarg("color", "k");

        cxxplot::Scatter<float> scatter(x_int, y_int, args);
        scatter.set_xlabel("x label");
        scatter.set_ylabel("y label");
        scatter.set_xlim(model.boundaries[0].x, model.boundaries[1].x);
        scatter.set_ylim(model.boundaries[0].y, model.boundaries[1].y);
        scatter.show();
    }

    void ModelPlotting::plot_gates_locations(const std::vector<Point2D> &gates) {
        std::vector<float> x_int;
        std::vector<float> y_int;

        for (const auto &gate : gates) {
            const Point2D agent_location = (Point2D &&) gate;
            x_int.emplace_back(agent_location.x);
            y_int.emplace_back(agent_location.y);
        }

        cxxplot::Kwargs args;
        args.add_kwarg("color", "r");
        args.add_kwarg("marker", "o");

        cxxplot::Scatter<float> scatter(x_int, y_int, args);
        scatter.set_xlabel("x label");
        scatter.set_ylabel("y label");
        scatter.show();
    }

    void ModelPlotting::plot_agents_trails(const Model &model) {
        cxxplot::Kwargs args;
        args.add_kwarg("color", "g");

        cxxplot::Plot<float> trails;

        std::vector<std::vector<float>> x_double;
        std::vector<std::vector<float>> y_double;

        for (const Agent &agent : model.agents) {

            std::vector<float> agent_location_history_x;
            std::vector<float> agent_location_history_y;

            for (const Point2D &point_2_d : agent.get_history_locations()) {
                agent_location_history_x.push_back(point_2_d.x);
                agent_location_history_y.push_back(point_2_d.y);
            }
            x_double.push_back(agent_location_history_x);
            y_double.push_back(agent_location_history_y);
        }

        for (long unsigned int i = 0; i < model.agents.size(); i++) {
            trails.add_data(x_double[i], y_double[i], args);
        }

        trails.show();
    }
} // namespace station_sim