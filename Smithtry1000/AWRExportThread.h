#include "Smithtry1000.h"

class AWRExportThread : public QThread
{
    Q_OBJECT
public:
    AWRExportThread(Smithtry1000* parent);
    bool getSuccess() const;

protected:
    void run() override;

private:
    Smithtry1000* m_parent;
    bool m_success;
};