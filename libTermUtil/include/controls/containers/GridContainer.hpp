#pragma once

#include "controls/containers/ContainerBase.hpp"

namespace terminal
{
enum class SizeType
{
    Relative,
    Absolute,
    Fit,
};

struct GridContainerColumn
{
    union {
        int absolute;
        float relative;
    } size;

    SizeType type;
};

typedef GridContainerColumn GridContainerRow;

class GridContainer : public ContainerBase
{
  private:
    std::vector<GridContainerColumn> columns;
    std::vector<GridContainerRow> rows;
    std::vector<ControlBase *> items;

  public:
    GridContainer();

    void Add(ControlBase *);
    void Add(ControlBase *, int col, int row);

    bool Remove(ControlBase *);
    bool Remove(int col, int row);

    void InsertRow(int before);
    void InsertCol(int before);

    int RowCount() const;
    int ColCount() const;
};
} // namespace terminal