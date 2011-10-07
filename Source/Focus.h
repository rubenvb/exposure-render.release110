#pragma once

#include "Preset.h"

class QFocus : public QPresetXML
{
	Q_OBJECT

public:
	QFocus(QObject* pParent = NULL);
	QFocus::QFocus(const QFocus& Other);
	QFocus& QFocus::operator=(const QFocus& Other);

	int			GetType(void) const;
	void		SetType(const int& Type);
	float		GetFocalDistance(void) const;
	void		SetFocalDistance(const float& FocalDistance);
	void		Reset(void);
	void		ReadXML(QDomElement& Parent);
	QDomElement	WriteXML(QDomDocument& DOM, QDomElement& Parent);

signals:
	void Changed(const QFocus& Focus);

private:
	int			m_Type;
	float		m_FocalDistance;
};
