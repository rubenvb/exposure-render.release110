
// Precompiled headers
#include "Stable.h"

#include "CameraWidget.h"
#include "MainWindow.h"
#include "RenderThread.h"

QCameraWidget::QCameraWidget(QWidget* pParent) :
	QWidget(pParent),
	m_MainLayout(),
	m_FilmWidget(),
	m_ApertureWidget(),
	m_ProjectionWidget(),
	m_FocusWidget(),
	m_PresetsWidget(NULL, "Camera", "Camera")
{
	m_MainLayout.setAlignment(Qt::AlignTop);
	setLayout(&m_MainLayout);

	m_MainLayout.addWidget(&m_PresetsWidget);
	m_MainLayout.addWidget(&m_FilmWidget);
	m_MainLayout.addWidget(&m_ApertureWidget);
	m_MainLayout.addWidget(&m_ProjectionWidget);
	m_MainLayout.addWidget(&m_FocusWidget);

	QObject::connect(&gCamera.GetFilm(), SIGNAL(Changed(const QFilm&)), &gCamera, SLOT(OnFilmChanged()));
	QObject::connect(&gCamera.GetAperture(), SIGNAL(Changed(const QAperture&)), &gCamera, SLOT(OnApertureChanged()));
	QObject::connect(&gCamera.GetProjection(), SIGNAL(Changed(const QProjection&)), &gCamera, SLOT(OnProjectionChanged()));
	QObject::connect(&gCamera.GetFocus(), SIGNAL(Changed(const QFocus&)), &gCamera, SLOT(OnFocusChanged()));
	QObject::connect(&m_PresetsWidget, SIGNAL(LoadPreset(const QString&)), this, SLOT(OnLoadPreset(const QString&)));
	QObject::connect(&m_PresetsWidget, SIGNAL(SavePreset(const QString&)), this, SLOT(OnSavePreset(const QString&)));
	QObject::connect(&gStatus, SIGNAL(LoadPreset(const QString&)), &m_PresetsWidget, SLOT(OnLoadPreset(const QString&)));
}

void QCameraWidget::OnLoadPreset(const QString& Name)
{
	m_PresetsWidget.LoadPreset(gCamera, Name);

	gScene.m_Camera.m_Target	= gCamera.GetTarget();
	gScene.m_Camera.m_From		= gCamera.GetFrom();
	gScene.m_Camera.m_Up		= gCamera.GetUp();
}

void QCameraWidget::OnSavePreset(const QString& Name)
{
	QCamera Preset(gCamera);
	Preset.SetName(Name);

	Preset.SetFrom(gScene.m_Camera.m_From);
	Preset.SetTarget(gScene.m_Camera.m_Target);
	Preset.SetUp(gScene.m_Camera.m_Up);

	// Add the preset
	m_PresetsWidget.SavePreset(Preset);
}

QSize QCameraWidget::sizeHint() const
{
	return QSize(20, 20);
}