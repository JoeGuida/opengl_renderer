#ifndef OPENGL_RENDERER_SHADER_HPP
#define OPENGL_RENDERER_SHADER_HPP

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "filesystem.hpp"

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <memory>
#include <unordered_map>

class Shader
{
public:
    std::string name;
    uint32_t id;

    Shader(const std::string& name, uint32_t id) : name(name), id(id) {}
    Shader(const Shader&) = default;
    Shader(Shader&&) = default;
    virtual ~Shader() = default;

    void set_uniform(const char* uniform_name, float value);
    void set_uniform(const char* uniform_name, double value);
    void set_uniform(const char* uniform_name, int value);
    void set_uniform(const char* uniform_name, const glm::mat4& value);
    void set_uniform(const char* uniform_name, const glm::vec3& value);
    void use();
};

class ShaderFactory {
private:
    friend class Shader;
    static std::unordered_map<std::string, std::shared_ptr<Shader>> shaders;

public:
    static std::shared_ptr<Shader> create(const std::string& name);
    static void compile(std::shared_ptr<Shader>& shader, const std::string& name);
    static std::shared_ptr<Shader> get(const std::string& name);
};

#endif