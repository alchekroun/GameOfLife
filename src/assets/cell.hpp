#pragma once

namespace gameoflife
{
    class cell
    {
        bool alive;

    public:
        cell(bool alive) : alive(alive) {}
        bool is_alive() { return alive; }
        void dies() { alive = false; }
        void lives() { alive = true; }
    };
}