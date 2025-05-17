#include "crow.h"
#include "CubeSolver.h"
#include <string>
#include <iostream>

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/solve")
        .methods("POST"_method, "OPTIONS"_method)
        ([](const crow::request& req) {
        crow::response res;
        res.add_header("Access-Control-Allow-Origin", "*");
        res.add_header("Access-Control-Allow-Methods", "POST, OPTIONS");
        res.add_header("Access-Control-Allow-Headers", "Content-Type");

        if (req.method == "OPTIONS"_method) {
            return res;
        }

        std::string cubeState;
        if (req.url_params.get("state")) {
            cubeState = req.url_params.get("state");
        }
        else {
            res.code = 400;
            res.body = "Missing cube state parameter";
            return res;
        }

        // Debug print to check the received state
        std::cout << "Received cube state: " << cubeState << std::endl;

        // Solve the cube
        std::string solution = solveCube(cubeState);

        // Optionally, check if the solution indicates an error.
        // For example, if solveCube returns an empty string or a specific error message,
        // you could handle it accordingly.

        res.body = solution;
        return res;
            });

    std::cout << "CubeBackend is running on port 5050" << std::endl;
    app.port(5050).multithreaded().run();
    return 0;
}
