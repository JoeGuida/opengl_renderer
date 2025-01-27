#include "shader.hpp"

std::unordered_map<std::string, std::shared_ptr<Shader>> ShaderFactory::shaders;

void Shader::set_uniform(const char* uniform_name, float value) {
    use();
    glUniform1f(glGetUniformLocation(id, uniform_name), value);
}

void Shader::set_uniform(const char* uniform_name, double value) {
    use();
    glUniform1d(glGetUniformLocation(id, uniform_name), value);
}

void Shader::set_uniform(const char* uniform_name, int value) {
    use();
    glUniform1i(glGetUniformLocation(id, uniform_name), value);
}

void Shader::set_uniform(const char* uniform_name, const glm::mat4& value) {
    use();
    glUniformMatrix4fv(glGetUniformLocation(id, uniform_name), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::set_uniform(const char* uniform_name, const glm::vec3& value) {
    use();
    glUniform3f(glGetUniformLocation(id, uniform_name), value.x, value.y, value.z);
}

void Shader::use() {
    glUseProgram(id);
}

std::shared_ptr<Shader> ShaderFactory::create(const std::string& name) {
    if (shaders.size() > 0 && shaders.find(name) != shaders.end()) {
        return shaders[name];
    }

    std::shared_ptr<Shader> shader = std::shared_ptr<Shader>(new Shader(name, 0));
    compile(shader, name);
    if (!shader) {
        std::cerr << "ERROR::SHADER::SHADER_COMPILATION_FAILED_FOR_SHADER: " << name << std::endl;
        exit(1);
    }
    shaders[name] = shader;
    return shader;
}

void ShaderFactory::compile(std::shared_ptr<Shader>& shader, const std::string& name) {
    // Retrieve vertex/fragment shader source code from filePath
    std::string vertex_shader_code, fragment_shader_code;
    std::ifstream vertex_shader_file, fragment_shader_file;
    std::stringstream vertex_shader_stream, fragment_shader_stream;

    // Ensure ifstream objects can throw exceptions
    vertex_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragment_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    std::string shader_path = FileSystem::get_path("/src/shaders/");
    std::string vertex_path = shader_path + name + ".vert";
    std::string fragment_path = shader_path + name + ".frag";

    try {
        // open files
        vertex_shader_file.open(vertex_path);
        fragment_shader_file.open(fragment_path);

        // read file's buffer contents into streams
        vertex_shader_stream << vertex_shader_file.rdbuf();
        fragment_shader_stream << fragment_shader_file.rdbuf();

        // close file handlers
        vertex_shader_file.close();
        fragment_shader_file.close();

        // convert stream into string
        vertex_shader_code = vertex_shader_stream.str();
        fragment_shader_code = fragment_shader_stream.str();
    }
    catch (std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        shader = nullptr;
        return;
    }
    const char* v_shader_code = vertex_shader_code.c_str();
    const char* f_shader_code = fragment_shader_code.c_str();

    // Compile shaders
    uint32_t vertex, fragment;
    int success;
    char info_log[512];

    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &v_shader_code, NULL);
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, info_log);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << std::endl;
        shader = nullptr;
        return;
    }

    // fragment shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &f_shader_code, NULL);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, info_log);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << std::endl;
        shader = nullptr;
        return;
    }

    // shader program
    shader->id = glCreateProgram();
    glAttachShader(shader->id, vertex);
    glAttachShader(shader->id, fragment);
    glLinkProgram(shader->id);

    glGetProgramiv(shader->id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader->id, 512, NULL, info_log);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info_log << std::endl;
        shader = nullptr;
        return;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

std::shared_ptr<Shader> ShaderFactory::get(const std::string& name) {
    return shaders[name];
}
