#include <QColor>
#include <QApplication>

#include <cg/visualization/viewer_adapter.h>
#include <cg/visualization/draw_util.h>

#include <cg/localization_point/localization_point.h>

using cg::point_2f;
using cg::point_2;
using cg::DCEL;
using cg::Line;

struct localization_point_viewer : cg::visualization::viewer_adapter
{
    DCEL * dcel_by_lines;

    localization_point_viewer()
    {
        dcel_by_lines = new DCEL(point_2(-400, -400), point_2(400, 400));
    }

    void draw(cg::visualization::drawer_type &drawer) const
    {
        drawer.set_color(Qt::red);

        if(have_first_point) {
            drawer.draw_point(first_point, 5);
        }

        if(have_second_point) {
            drawer.draw_point(second_point, 5);
        }

        if(have_first_point && have_second_point) {
            dcel_by_lines->add_line(first_point, second_point);
        }

        drawer.set_color(Qt::blue);
        drow_all_lines(drawer);

    }

    void print(cg::visualization::printer_type &p) const
    {

    }


    bool on_release(const point_2f &p)
    {
        if(!have_first_point && !have_second_point) {
            first_point = p;
            have_first_point= true;
            return true;
        }
        if(have_first_point && !have_second_point) {
            second_point = p;
            have_second_point = true;
            return true;
        }
        if(have_first_point && have_second_point) {
            have_second_point = false;
            first_point = p;
            return true;
        }


    }

    bool on_key(int key)
    {

    }

    bool on_move(const point_2f &p) {
        moving_point = p;
    }


    void drow_all_lines(cg::visualization::drawer_type &drawer) const {
        for(int i = 0; i < dcel_by_lines->lines.size(); i++) {
            drawer.draw_line(dcel_by_lines->lines[i]->first_point, dcel_by_lines->lines[i]->second_point);
        }
    }

private:
    bool have_first_point = false;
    bool have_second_point = false;
    point_2 first_point;
    point_2 second_point;
    point_2 moving_point;

};

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    localization_point_viewer viewer;
    cg::visualization::run_viewer(&viewer, "Quadtree");
}

