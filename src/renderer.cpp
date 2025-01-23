#include "renderer.hpp"

uint32_t Renderer::VAO;
uint32_t Renderer::VBO;
uint32_t Renderer::EBO;
#define PI 3.14159265358979323846

void Renderer::initialize() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
}

void Renderer::draw(const Cylinder& cylinder, Shader& shader) {
    std::vector<Vertex> vertices = cylinder.get_vertices();
    std::vector<uint32_t> indices = cylinder.get_indices();

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    glm::mat4 model(1.0f);
    model = glm::translate(model, cylinder.transform.position);
    shader.set_uniform("model", model);
    shader.set_uniform("Material.diffuse", cylinder.material.diffuse);
    shader.set_uniform("Material.specular", cylinder.material.specular);
    shader.set_uniform("Material.alpha", cylinder.material.alpha);

    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
}

void Renderer::draw(const Icosahedron& icosahedron, Shader& shader) {
    std::array<Vertex, 12> vertices = icosahedron.get_vertices();
    std::array<uint32_t, 60> indices = icosahedron.get_indices();

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    glm::mat4 model(1.0f);
    model = glm::translate(model, icosahedron.transform.position);
    model = glm::rotate(model, icosahedron.transform.euler_angles.z, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, icosahedron.transform.scale);
    shader.set_uniform("model", model);
    shader.set_uniform("Material.diffuse", icosahedron.material.diffuse);
    shader.set_uniform("Material.specular", icosahedron.material.specular);
    shader.set_uniform("Material.alpha", icosahedron.material.alpha);

    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
}

void Renderer::draw(const Mesh& mesh, Shader& shader) {
    std::vector<Vertex> vertices = mesh.get_vertices();
    std::vector<uint32_t> indices = mesh.get_indices();

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    glm::mat4 model(1.0f);
    model = glm::translate(model, mesh.transform.position);
    model = glm::rotate(model, mesh.transform.euler_angles.z, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, mesh.transform.scale);
    shader.set_uniform("model", model);
    shader.set_uniform("Material.diffuse", mesh.material.diffuse);
    shader.set_uniform("Material.specular", mesh.material.specular);
    shader.set_uniform("Material.alpha", mesh.material.alpha);

    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
}

void Renderer::draw(const Octahedron& octahedron, Shader& shader) {
    std::array<Vertex, 6> vertices = octahedron.get_vertices();
    std::array<uint32_t, 24> indices = octahedron.get_indices();

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    glm::mat4 model(1.0f);
    model = glm::translate(model, octahedron.transform.position);
    model = glm::rotate(model, octahedron.transform.euler_angles.z, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, octahedron.transform.scale);
    shader.set_uniform("model", model);
    shader.set_uniform("Material.diffuse", octahedron.material.diffuse);
    shader.set_uniform("Material.specular", octahedron.material.specular);
    shader.set_uniform("Material.alpha", octahedron.material.alpha);

    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
}

void Renderer::draw(const Rectangle& rectangle, Shader& shader) {
    std::array<Vertex, 24> vertices = rectangle.get_vertices();
    std::array<uint32_t, 36> indices = rectangle.get_indices();

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    glm::mat4 model(1.0f);
    model = glm::translate(model, rectangle.transform.position);
    model = glm::rotate(model, rectangle.transform.euler_angles.z, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, rectangle.transform.scale);
    shader.set_uniform("model", model);
    shader.set_uniform("Material.diffuse", rectangle.material.diffuse);
    shader.set_uniform("Material.specular", rectangle.material.specular);
    shader.set_uniform("Material.alpha", rectangle.material.alpha);

    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
}

void Renderer::draw(const Sphere& sphere, Shader& shader) {
    Icosahedron icosahedron(sphere.radius, sphere.transform, sphere.material);

    std::array<Vertex, 12> icosahedron_vertices = icosahedron.get_vertices();
    std::array<uint32_t, 60> icosahedron_indices = icosahedron.get_indices();
    std::vector<Triangle> triangles;
    
    for (int i = 0; i < icosahedron_indices.size(); i += 3) {
        int i0 = icosahedron_indices[i];
        int i1 = icosahedron_indices[i + 1];
        int i2 = icosahedron_indices[i + 2];
        Triangle triangle(
            glm::normalize(icosahedron_vertices[i0].position),
            glm::normalize(icosahedron_vertices[i1].position),
            glm::normalize(icosahedron_vertices[i2].position)
        );
        triangles.push_back(triangle);
    }
    triangles = subdivide_triangles(triangles, sphere.depth);

    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    int j = 0;
    for (int i = 0; i < triangles.size(); i++) {
        Vertex v0(triangles[i].points[0] * sphere.radius, glm::vec3(0.0f), glm::vec2(0.0f, 0.0f));
        Vertex v1(triangles[i].points[1] * sphere.radius, glm::vec3(0.0f), glm::vec2(0.0f, 0.0f));
        Vertex v2(triangles[i].points[2] * sphere.radius, glm::vec3(0.0f), glm::vec2(0.0f, 0.0f));
        vertices.push_back(v0);
        vertices.push_back(v1);
        vertices.push_back(v2);
        indices.push_back(j);
        indices.push_back(j + 1);
        indices.push_back(j + 2);
        j += 3;
    }

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    glm::mat4 model(1.0f);
    model = glm::translate(model, sphere.transform.position);
    shader.set_uniform("model", model);
    shader.set_uniform("Material.diffuse", sphere.material.diffuse);
    shader.set_uniform("Material.specular", sphere.material.specular);
    shader.set_uniform("Material.alpha", sphere.material.alpha);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
}

void Renderer::draw(const Tetrahedron& tetrahedron, Shader& shader) {
    std::array<Vertex, 4> vertices = tetrahedron.get_vertices();
    std::array<uint32_t, 12> indices = tetrahedron.get_indices();

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    glm::mat4 model(1.0f);
    model = glm::translate(model, tetrahedron.transform.position);
    model = glm::rotate(model, tetrahedron.transform.euler_angles.z, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, tetrahedron.transform.scale);
    shader.set_uniform("model", model);
    shader.set_uniform("Material.diffuse", tetrahedron.material.diffuse);
    shader.set_uniform("Material.specular", tetrahedron.material.specular);
    shader.set_uniform("Material.alpha", tetrahedron.material.alpha);

    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
}

std::vector<Triangle> Renderer::subdivide_triangles(const std::vector<Triangle>& triangles, int depth) {
    if (depth == 0) {
        return triangles;
    }

    std::vector<Triangle> new_triangles;
    for (int i = 0; i < triangles.size(); i++) {
        glm::vec3 ab = glm::normalize((triangles[i].a() + triangles[i].b()) / 2.0f);
        glm::vec3 bc = glm::normalize((triangles[i].b() + triangles[i].c()) / 2.0f);
        glm::vec3 ac = glm::normalize((triangles[i].a() + triangles[i].c()) / 2.0f);

        Triangle t0(triangles[i].a(), ab, ac);
        Triangle t1(ab, ac, bc);
        Triangle t2(ac, bc, triangles[i].c());
        Triangle t3(ab, triangles[i].b(), bc);

        new_triangles.push_back(t0);
        new_triangles.push_back(t1);
        new_triangles.push_back(t2);
        new_triangles.push_back(t3);
    }

    return subdivide_triangles(new_triangles, --depth);
}