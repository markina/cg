#include <cg/primitives/point.h>

#include <vector>

namespace cg
{

    struct Line
    {
        point_2 first_point, second_point;

        Line()
        {
        }

        Line(point_2 const &p1, point_2 const &p2)
                : first_point(p1), second_point(p2)
        {
        }
    };

    struct DCEL
    {
        std::vector<Line *> lines;

        DCEL(point_2 const &p1, point_2 const &p2) {
            lines.push_back(new Line(p1, point_2(p2.x, p1.y)));
            lines.push_back(new Line(p1, point_2(p1.x, p2.y)));
            lines.push_back(new Line(p2, point_2(p2.x, p1.y)));
            lines.push_back(new Line(p2, point_2(p1.x, p2.y)));
        }

        void add_line(point_2 const &p1, point_2 const &p2) {
            lines.push_back(new Line(p1, p2));
        }
    };




    struct localization_point
    {
        std::vector<localization_point *> children;
        point_2 left_down_corner;
        point_2 right_up_corner;
        point_2 *point;


        localization_point()
        {
            point = nullptr;
        }

        localization_point(point_2 const &left_down_corner, point_2 const &right_up_corner)
                : left_down_corner(left_down_corner), right_up_corner(right_up_corner)
        {
            point = nullptr;
        }

        void add_point(point_2 new_point)
        {
            if (!is_square_consist_point(left_down_corner, right_up_corner, new_point))
            {
                return;
            }

            if (children.empty())
            {
                if (!point)
                {
                    point = new point_2(new_point);
                } else
                {
                    for (int i = 0; i < 4; i++)
                    {
                        children.push_back(new localization_point());
                        ini_corners(children[i], i);
                        children[i]->add_point(new_point);
                        children[i]->add_point(*point);
                    }
                    point = nullptr;
                }
            }
            else
            {
                for (int i = 0; i < 4; i++)
                {
                    children[i]->add_point(new_point);
                }
            }
        }

        bool is_square_consist_point(point_2 left_down_corner, point_2 right_up_corner, point_2 point)
        {
            return left_down_corner.x <= point.x && left_down_corner.y <= point.y &&
                    right_up_corner.x > point.x && right_up_corner.y > point.y;
        }


        void ini_corners(localization_point *q, int num_sq)
        {
            switch (num_sq)
            {
                case 0:
                    q->left_down_corner.x = (left_down_corner.x + right_up_corner.x) / 2;
                    q->left_down_corner.y = left_down_corner.y;
                    q->right_up_corner.x = right_up_corner.x;
                    q->right_up_corner.y = (left_down_corner.y + right_up_corner.y) / 2;
                    break;
                case 1:
                    q->left_down_corner.x = left_down_corner.x;
                    q->left_down_corner.y = left_down_corner.y;
                    q->right_up_corner.x = (left_down_corner.x + right_up_corner.x) / 2;
                    q->right_up_corner.y = (left_down_corner.y + right_up_corner.y) / 2;
                    break;
                case 2:
                    q->left_down_corner.x = left_down_corner.x;
                    q->left_down_corner.y = (left_down_corner.y + right_up_corner.y) / 2;
                    q->right_up_corner.x = (left_down_corner.x + right_up_corner.x) / 2;
                    q->right_up_corner.y = right_up_corner.y;
                    break;
                case 3:
                    q->left_down_corner.x = (left_down_corner.x + right_up_corner.x) / 2;
                    q->left_down_corner.y = (left_down_corner.y + right_up_corner.y) / 2;
                    q->right_up_corner.x = right_up_corner.x;
                    q->right_up_corner.y = right_up_corner.y;
                    break;
            }
        }

    };


}