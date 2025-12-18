-- =========================================================
-- Asset Database Schema
-- Engine: Purity
-- Database: SQLite
-- =========================================================

PRAGMA foreign_keys = ON;

-- =========================================================
-- Schema Versioning
-- =========================================================
CREATE TABLE IF NOT EXISTS schema_version (
                                              version INTEGER NOT NULL
);

INSERT INTO schema_version (version)
SELECT 1
WHERE NOT EXISTS (SELECT 1 FROM schema_version);

-- =========================================================
-- Assets Table
-- Every asset in the project lives here
-- Imported assets, native assets, scenes, project file
-- =========================================================
CREATE TABLE IF NOT EXISTS assets (
                                      id              INTEGER PRIMARY KEY AUTOINCREMENT,

                                      uuid            TEXT NOT NULL UNIQUE,
                                      name            TEXT NOT NULL,

                                      asset_type      INTEGER NOT NULL,
                                      representation  INTEGER NOT NULL,

                                      meta_path       TEXT NOT NULL,
                                      source_path     TEXT,
                                      binary_path     TEXT,

                                      is_dirty        INTEGER NOT NULL DEFAULT 0,
                                      is_deleted      INTEGER NOT NULL DEFAULT 0,

                                      created_at      INTEGER NOT NULL,
                                      modified_at     INTEGER NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_assets_uuid
    ON assets(uuid);

CREATE INDEX IF NOT EXISTS idx_assets_type
    ON assets(asset_type);

-- =========================================================
-- Import State
-- Used to detect reimport requirements quickly
-- =========================================================
CREATE TABLE IF NOT EXISTS asset_import_state (
                                                  asset_id        INTEGER PRIMARY KEY,
                                                  import_hash     TEXT NOT NULL,
                                                  source_hash     TEXT NOT NULL,

                                                  FOREIGN KEY(asset_id)
                                                      REFERENCES assets(id)
                                                      ON DELETE CASCADE
);

-- =========================================================
-- Asset Dependencies
-- Used by scenes, materials, shaders, etc
-- =========================================================
CREATE TABLE IF NOT EXISTS asset_dependencies (
                                                  asset_id            INTEGER NOT NULL,
                                                  depends_on_asset_id INTEGER NOT NULL,

                                                  PRIMARY KEY (asset_id, depends_on_asset_id),

                                                  FOREIGN KEY(asset_id)
                                                      REFERENCES assets(id)
                                                      ON DELETE CASCADE,

                                                  FOREIGN KEY(depends_on_asset_id)
                                                      REFERENCES assets(id)
                                                      ON DELETE CASCADE
);

CREATE INDEX IF NOT EXISTS idx_dependencies_asset
    ON asset_dependencies(asset_id);

CREATE INDEX IF NOT EXISTS idx_dependencies_depends
    ON asset_dependencies(depends_on_asset_id);

-- =========================================================
-- Asset Tags (Optional but useful)
-- =========================================================
CREATE TABLE IF NOT EXISTS asset_tags (
                                          asset_id    INTEGER NOT NULL,
                                          tag         TEXT NOT NULL,

                                          PRIMARY KEY (asset_id, tag),

                                          FOREIGN KEY(asset_id)
                                              REFERENCES assets(id)
                                              ON DELETE CASCADE
);

CREATE INDEX IF NOT EXISTS idx_asset_tags_tag
    ON asset_tags(tag);

-- =========================================================
-- Project Settings (Key-Value)
-- =========================================================
CREATE TABLE IF NOT EXISTS project_settings (
                                                key     TEXT PRIMARY KEY,
                                                value   TEXT NOT NULL
);
