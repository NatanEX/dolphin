// Copyright 2016 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#pragma once

#include <QDialog>
#include <memory>

// Qt versions prior to 5.9 don't support C++17 nested namespaces in moc so we have to if-guard
// this header
#ifndef Q_MOC_RUN
#include "DiscIO/Volume.h"
#endif

#include "UICommon/GameFile.h"

class QStandardItem;
class QStandardItemModel;
class QTreeView;

namespace DiscIO
{
class FileInfo;
struct Partition;
};  // namespace DiscIO

class FilesystemWidget final : public QWidget
{
  Q_OBJECT
public:
  explicit FilesystemWidget(const UICommon::GameFile& game);

private:
  void CreateWidgets();
  void ConnectWidgets();
  void PopulateView();
  void PopulateDirectory(int partition_id, QStandardItem* root, const DiscIO::Partition& partition);
  void PopulateDirectory(int partition_id, QStandardItem* root, const DiscIO::FileInfo& directory);

  void ShowContextMenu(const QPoint&);

  void ExtractPartition(const DiscIO::Partition& partition, const QString& out);
  void ExtractDirectory(const DiscIO::Partition& partition, const QString& path,
                        const QString& out);
  void ExtractFile(const DiscIO::Partition& partition, const QString& path, const QString& out);
  bool ExtractSystemData(const DiscIO::Partition& partition, const QString& out);
  void CheckIntegrity(const DiscIO::Partition& partition);

  DiscIO::Partition GetPartitionFromID(int id);

  QStandardItemModel* m_tree_model;
  QTreeView* m_tree_view;

  UICommon::GameFile m_game;
  std::unique_ptr<DiscIO::Volume> m_volume;
};
