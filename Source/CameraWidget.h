#pragma once

#include "Camera.h"
#include "FilmWidget.h"
#include "ApertureWidget.h"
#include "ProjectionWidget.h"
#include "FocusWidget.h"
#include "PresetsWidget.h"

class QCameraWidget : public QWidget
{
    Q_OBJECT

public:
    QCameraWidget(QWidget* pParent = NULL);

	virtual QSize sizeHint() const;

public slots:
	void OnLoadPreset(const QString& Name);
	void OnSavePreset(const QString& Name);

private:
	QGridLayout					m_MainLayout;
	QFilmWidget					m_FilmWidget;
	QApertureWidget				m_ApertureWidget;
	QProjectionWidget			m_ProjectionWidget;
	QFocusWidget				m_FocusWidget;
	QPresetsWidget<QCamera>		m_PresetsWidget;
};