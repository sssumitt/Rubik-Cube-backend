#include "crow.h"
#include "CubeSolver.h"
#include <string>
#include <iostream>
#include <cstdlib>

int main() {
    crow::SimpleApp app;

    // Health check for load balancers / Kubernetes probes
    CROW_ROUTE(app, "/health")([]() { return "ok"; });

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


        res.body = solution;
        return res;
            });

    // Read port from the PORT env var (used by Render, Cloud Run, k8s); default 5050
    const char* portEnv = std::getenv("PORT");
    int port = portEnv ? std::atoi(portEnv) : 5050;

    std::cout << "CubeBackend is running on port " << port << std::endl;
    app.port(port).multithreaded().run();
    return 0;
}
