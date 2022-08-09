/**
 * @file Compute.h
 * @author Michael Dias
 * @brief this class provides an interface for algorithms for solving calculator problems
 * @version 1.0
 */

#ifndef COMPUTE_H
#define COMPUTE_H

#include <string>
#include <vector>


class Compute{
    public:
        virtual std::vector<std::string> solve(const std::string&) const{};
        virtual std::vector<std::string> solve(const std::vector<std::string>&) const {};
        virtual std::vector<std::vector<double>> solve(const std::vector<std::vector<double>>&, std::vector<std::vector<double>>&,
                           char[3], double scalar1, double scalar2) const {};
        virtual std::string solve(const std::vector<double>&, const std::vector<double>&, const std::string&) {};
        virtual double solve(const std::string&, const std::string&) {};
};

#endif //COMPUTE_H