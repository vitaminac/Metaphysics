#include <iostream>
#include <fstream>
#include "gengine.h"
#include "test.h"

using namespace gengine;
using namespace graphic;
using namespace geometry;

void test_vector() {
    auto v = vec3(1.0, 2.0, 3.0);
    std::cout << v << std::endl;

    auto a = vec3(1.0, 2.0, 3.0);

    test(a.module(), 3.74166, "3.74166", 0.001);
    std::cout << "The module of " << a << " is " << a.module() << std::endl;

    auto b = vec3(1.0, 3.0, 5.0);
    test(a + b, vec3(2, 5, 8), "(1,2,3)+(1,3,5)=(2,5,8)");
    std::cout << a << " + " << b << " = " << a + b << std::endl;
    test(a - b, vec3(0, -1, -2), "(1,2,3)-(1,3,5)=(0,-1,-2)");
    std::cout << a << " - " << b << " = " << a - b << std::endl;

    test(3 * a, vec3(3, 6, 9), "3 per (1,2,3) is (3,6,9)");
    std::cout << a << " per 3 is " << a * 3 << std::endl;
    std::cout << "3 per " << a << " is " << 3 * a << std::endl;

    test(-v, vec3(-1, -2, -3), "The opposite of (1,2,3) is (-1,-2,-3)");
    std::cout << "The opposite of " << v << " is " << -v << std::endl;

    auto u = a.normalize();
    test(u.getX(), 0.267261, "The unit vector of (1,2,3) is (0.267261,0.534522,0.801784)", 0.001);
    test(u.getY(), 0.534522, "The unit vector of (1,2,3) is (0.267261,0.534522,0.801784)", 0.001);
    test(u.getZ(), 0.801784, "The unit vector of (1,2,3) is (0.267261,0.534522,0.801784)", 0.001);
    std::cout << "The unit vector of " << a << " is " << a.normalize() << std::endl;

    test(a.dot(b), 22, "The dot product of (1,2,3) with (1,3,5) is 22", 0);
    std::cout << "The dot product of " << a << " with " << b << " is " << a.dot(b) << std::endl;

    test(a.cross(b), vec3(1, -2, 1), "The cross product of (1,2,3) with (1,3,5) is (1,-2,1)");
    std::cout << "The cross product of " << a << " with " << b << " is " << a.cross(b) << std::endl;
    test(b.cross(a), vec3(-1, 2, -1), "The cross product of (1,3,5) with (1,2,3) is (-1,2,-1)");
    std::cout << "The cross product of " << b << " with " << a << " is " << b.cross(a) << std::endl;

    test(a.includedAngle(b), 0.110884, "The angle between (1,2,3) and (1,3,5) is 0.110884", 0.001);
    std::cout << "The angle between " << a << " and " << b << " is " << a.includedAngle(b) << std::endl;

}

void test_mesh() {
    TriangleMesh mesh;
    std::ifstream off_in("16Triangles.off");
    std::cout << "Reading file 16Triangles.off" << std::endl;
    mesh.importFromOff(off_in);
    std::cout << "The mesh was restored" << std::endl << mesh;

    std::ofstream off_out("16Triangles_out.off");
    std::cout << "Saving as the .off format" << std::endl;
    mesh.saveAsOff(off_out);

    test(mesh.facetArea(mesh.faces[0]), 0.545776, "The surface' area of the Triangle a:6, b:7, c: 8 is 0.545776", 0.0001);
    std::cout << "The surface' area of " << mesh.faces[0] << " is " << mesh.facetArea(mesh.faces[0]) << std::endl;

    test(mesh.surfaceNormal(mesh.faces[0]), vec3(0, 0, 1), "The surface normal associated with the Triangle a:6, b:7, c: 8 is (0,0,1)");
    std::cout << "The surface normal associated with " << mesh.faces[0] << " is " << mesh.surfaceNormal(mesh.faces[0]) << std::endl;

    test(mesh.vertexNormal(0), vec3(0, 0, 1), "The vertex normal associated with vectex 0 (0,-0.942809,0) is (0,0,1)");
    std::cout << "The vertex normal associated with vectex 0 " << mesh.vertices[0] << " is " << mesh.vertexNormal(0) << std::endl;

}

void test_mat4() {
    mat4 position = mat4::translation(vec3(2, 3, 4));

    vec4& c = position.columns[3];
    std::cout << c << std::endl;

    position = position * mat4::identity();

    c = position.columns[3];
    std::cout << c << std::endl;
}

void test_file_utils() {
    std::string cpp = FileUtils::read_file("main.cpp");
    std::cout << cpp << std::endl;
}

int main()
{
    test_vector();
    test_mesh();
    test_mat4();
    test_file_utils();

    const int window_width = 960;
    const int window_height = 540;
    Window window("Game Engine", window_width, window_height);
    // window.setBackgroundColor(1.0f, 1.0f, 1.0f, 1.0f);

    GLfloat vertices[] =
    {
        0, 0, 0,
        0, 3, 0,
        8, 3, 0,
        8, 0, 0
    };

    GLushort indices[] =
    {
        0, 1, 2,
        2, 3, 0
    };

    GLfloat colorsA[] =
    {
        1, 0, 1, 1,
        1, 0, 1, 1,
        1, 0, 1, 1,
        1, 0, 1, 1
    };

    GLfloat colorsB[] =
    {
        0.2f, 0.3f, 0.8f, 1,
        0.2f, 0.3f, 0.8f, 1,
        0.2f, 0.3f, 0.8f, 1,
        0.2f, 0.3f, 0.8f, 1
    };

    VertexArrayObject sprite1, sprite2;
    IndexedVertexBufferObject ibo(indices, 6);

    sprite1.addBuffer(new VertexBufferObject(vertices, 4 * 3, 3), 0);
    sprite1.addBuffer(new VertexBufferObject(colorsA, 4 * 4, 4), 1);

    sprite2.addBuffer(new VertexBufferObject(vertices, 4 * 3, 3), 0);
    sprite2.addBuffer(new VertexBufferObject(colorsB, 4 * 4, 4), 1);

    const float content_width = 16;
    const float content_height = 9;
    mat4 ortho = mat4::orthographic(vec3(0.0f, 0.0f, -1.0f), vec3(content_width, content_height, 1.0f));

    Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
    shader.enable();
    
    shader.setUniformMat4("projection_matrix", ortho);
    shader.setUniformMat4("model_matrix", mat4::rotation(vec3::FORWARD, 10.0f) * mat4::translation(vec3(4, 3, 0)));
    
    shader.setUniformVector2("light_position", vec2(4.0f, 1.5f));
    shader.setUniformVector4("colour", vec4(0.2f, 0.3f, 0.8f, 1.0f));

    while (!window.closed()) {
        window.clear();
        const Position& p = window.getMousePosition();
        shader.setUniformVector2("light_position", vec2((float)(p.x * content_width / window_width), (float)(content_height - p.y * content_height / window_height)));

        sprite1.bind();
        ibo.bind();
        shader.setUniformMat4("model_matrix", mat4::translation(vec3(4, 3, 0)));
        glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
        ibo.unbind();
        sprite1.unbind();

        sprite2.bind();
        ibo.bind();
        shader.setUniformMat4("model_matrix", mat4::translation(vec3(0, 0, 0)));
        glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
        ibo.unbind(); // TODO: why we need bind twice
        sprite2.unbind();

        window.update();
    }
    return 0;
}