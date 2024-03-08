#include "myHomeWork.hpp"
#include"myHomeWork.hpp"

void HollowCircle::setColr(const float R, const float G, const float B)
{
	float r = R < 0 ? 0 : R;
	float g = G < 0 ? 0 : G;
	float b = B < 0 ? 0 : B;

	//线性映射，将一个 >1 的数映射为 <1 的数
	auto linearMap = [](const float num)->const float {
		if (num <= 1)	return num;
		if (num >= 255)	return 1.0f;

		return num * 1.0f / 255.0f;
	};

	r = linearMap(r);
	g = linearMap(g);
	b = linearMap(b);

	glColor3f(r, g, b);
}

void HollowCircle::paint()
{
	glBegin(GL_TRIANGLES);
	constexpr int n = 100;
	constexpr float pi = 3.14159f;

	if (start_angle < end_angle) {
		for (int i = n * start_angle; i < n * end_angle; i++) {
			float angle = i / (float)n * pi * 2;
			float next_angle = (i + 1) / (float)n * pi * 2;
			/*第一个三角形的三个点坐标*/
			//点A坐标
			float first_triangle_A_x = cosf(angle) * inner_raduis + x;
			float first_triangle_A_y = sinf(angle) * inner_raduis + y;
			//点B坐标
			float first_triangle_B_x = cosf(angle) * top_raduis + x;
			float first_triangle_B_y = sinf(angle) * top_raduis + y;
			//点C坐标
			float first_triangle_C_x = cosf(next_angle) * top_raduis + x;
			float first_triangle_C_y = sinf(next_angle) * top_raduis + y;

			/*第二个三角形的三个点坐标*/
			//点A坐标
			float second_triangle_A_x = first_triangle_A_x;
			float second_triangle_A_y = first_triangle_A_y;
			//点B坐标
			float second_triangle_B_x = cosf(next_angle) * inner_raduis + x;
			float second_triangle_B_y = sinf(next_angle) * inner_raduis + y;
			//点C坐标
			float second_triangle_C_x = first_triangle_C_x;
			float second_triangle_C_y = first_triangle_C_y;

			glVertex3f(first_triangle_A_x, first_triangle_A_y, 0.0f);
			glVertex3f(first_triangle_B_x, first_triangle_B_y, 0.0f);
			glVertex3f(first_triangle_C_x, first_triangle_C_y, 0.0f);

			glVertex3f(second_triangle_A_x, second_triangle_A_y, 0.0f);
			glVertex3f(second_triangle_B_x, second_triangle_B_y, 0.0f);
			glVertex3f(second_triangle_C_x, second_triangle_C_y, 0.0f);
		}
	}
	else if (start_angle == end_angle) {
		CHECK_GL(glEnd());
		return;
	}
	else {
		for (int i = n * start_angle; i > n * end_angle; i--) {
			float angle = i / (float)n * pi * 2;
			float next_angle = (i + 1) / (float)n * pi * 2;
			/*第一个三角形的三个点坐标*/
			//点A坐标
			float first_triangle_A_x = cosf(angle) * inner_raduis + x;
			float first_triangle_A_y = sinf(angle) * inner_raduis + y;
			//点B坐标
			float first_triangle_B_x = cosf(angle) * top_raduis + x;
			float first_triangle_B_y = sinf(angle) * top_raduis + y;
			//点C坐标
			float first_triangle_C_x = cosf(next_angle) * top_raduis + x;
			float first_triangle_C_y = sinf(next_angle) * top_raduis + y;

			/*第二个三角形的三个点坐标*/
			//点A坐标
			float second_triangle_A_x = first_triangle_A_x;
			float second_triangle_A_y = first_triangle_A_y;
			//点B坐标
			float second_triangle_B_x = cosf(next_angle) * inner_raduis + x;
			float second_triangle_B_y = sinf(next_angle) * inner_raduis + y;
			//点C坐标
			float second_triangle_C_x = first_triangle_C_x;
			float second_triangle_C_y = first_triangle_C_y;

			glVertex3f(first_triangle_A_x, first_triangle_A_y, 0.0f);
			glVertex3f(first_triangle_B_x, first_triangle_B_y, 0.0f);
			glVertex3f(first_triangle_C_x, first_triangle_C_y, 0.0f);

			glVertex3f(second_triangle_A_x, second_triangle_A_y, 0.0f);
			glVertex3f(second_triangle_B_x, second_triangle_B_y, 0.0f);
			glVertex3f(second_triangle_C_x, second_triangle_C_y, 0.0f);
		}
	}
	CHECK_GL(glEnd());
}
