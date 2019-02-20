#include "ball.h"
#include "main.h"

Arrow::Arrow(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation_x = 0;
    this->rotation = 0;
    this->cur_enemy = 0;
    // this->rotation_y = 0;
    // this->rotation_z = 0;
    // speed = 1;

    static const GLfloat vertex_buffer_data[] = {
        -10.0f, 0.0f, 0.0f, // triangle 1 : begin
        10.0f, 0.0f, 0.0f,
        -10.0f, 60.0f, 0.0f, // triangle 1 : end
        10.0f, 0.0f, 0.0f,
        -10.0f, 60.0f, 0.0f,
        10.0f, 60.0f, 0.0f,
    }; 

    static const GLfloat vertex_buffer_data1[] = {
        -15.0f, 60.0f, 0.0f, // triangle 1 : begin
        15.0f, 60.0f, 0.0f,
        0.0f, 80.0f, 0.0f, // triangle 1 : end
    };

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    this->object = create3DObject(GL_TRIANGLES, 3*2, vertex_buffer_data, color, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data1, color, GL_FILL);
}

void Arrow::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation_x * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 rotatey    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate * rotatey);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
}

void Arrow::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Arrow::tick(Ball plane, Enemy current) 
{
	float angle = atan ( (plane.position.z - current.position.z)/(plane.position.x - current.position.x) ) * (180.0f/M_PI);

	if(plane.position.z > current.position.z )
	{
		if(angle >= 0)
			this->rotation = plane.rotation_y - 90 + angle;
		else
			this->rotation = plane.rotation_y + 90 + angle;
	}
	else
	{
		if(angle >= 0)
			this->rotation = plane.rotation_y + 90 + angle;
		else
			this->rotation = plane.rotation_y - 90 + angle;

	}
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

