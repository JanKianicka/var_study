CREATE TABLE IF NOT EXISTS topo_podklady.tvm10_listoklad
(
    gid double precision NOT NULL,
    cislo_ml character varying COLLATE pg_catalog."default",
    poznamka character varying COLLATE pg_catalog."default",
    mi_style character varying COLLATE pg_catalog."default",
    vlozene character varying COLLATE pg_catalog."default",
    upravene character varying COLLATE pg_catalog."default",
    lbl_x double precision,
    lbl_y double precision,
    lbl_rot double precision,
    lbl_font character varying COLLATE pg_catalog."default",
    lbl_size double precision,
    lbl_style character varying COLLATE pg_catalog."default",
    lbl_color character varying COLLATE pg_catalog."default",
    lbl_roz double precision,
    lbl_vis bigint,
    geom geometry(Polygon,3046),
    CONSTRAINT tvm10_listoklad_pkey PRIMARY KEY (gid)
)

TABLESPACE pg_default;

ALTER TABLE IF EXISTS topo_podklady.tvm10_listoklad
    OWNER to kianicka_admin;

CREATE INDEX IF NOT EXISTS tvm10_listoklad_geom_idx
    ON topo_podklady.tvm10_listoklad USING gist
    (geom)
    TABLESPACE pg_default;
	
REVOKE ALL ON TABLE topo_podklady.tvm10_listoklad FROM PUBLIC;

GRANT SELECT ON TABLE topo_podklady.tvm10_listoklad TO PUBLIC;

GRANT ALL ON TABLE topo_podklady.tvm10_listoklad TO kianicka_admin;

COMMENT ON TABLE topo_podklady.tvm10_listoklad
    IS 'Listoklad topografických (vojenských) máp TVM 1 : 10 000 (súradnicový systém ETRS89 / UTM zone 34N (N-E), EPSG: 3046).';

COMMENT ON COLUMN topo_podklady.tvm10_listoklad.cislo_ml
    IS 'Číslo mapového listu Topografickej vojenskej mapy 1:10 000.';

COMMENT ON COLUMN topo_podklady.tvm10_listoklad.poznamka
    IS 'Rôzne poznámky.';

COMMENT ON COLUMN topo_podklady.tvm10_listoklad.mi_style
    IS 'Štýl entity (farba, šrafa) pre program MapInfo.';

COMMENT ON COLUMN topo_podklady.tvm10_listoklad.vlozene
    IS 'Dátum a čas vloženia záznamu.';

COMMENT ON COLUMN topo_podklady.tvm10_listoklad.upravene
    IS 'Dátum a čas upravenia záznamu.';

COMMENT ON COLUMN topo_podklady.tvm10_listoklad.lbl_x
    IS 'Pozícia popisu (Easting).';

COMMENT ON COLUMN topo_podklady.tvm10_listoklad.lbl_y
    IS 'Pozícia popisu (Northing).';

COMMENT ON COLUMN topo_podklady.tvm10_listoklad.lbl_rot
    IS 'Rotácia popisky.';

COMMENT ON COLUMN topo_podklady.tvm10_listoklad.lbl_font
    IS 'Typ písma popisky.';

COMMENT ON COLUMN topo_podklady.tvm10_listoklad.lbl_size
    IS 'Veľkosť písma popisky.';

COMMENT ON COLUMN topo_podklady.tvm10_listoklad.lbl_style
    IS 'Štýl písma popisky (tučné, kurzíva a pod...).';

COMMENT ON COLUMN topo_podklady.tvm10_listoklad.lbl_color
    IS 'Farba písma popisky.';

COMMENT ON COLUMN topo_podklady.tvm10_listoklad.lbl_roz
    IS 'Rozostup písmen popisky.';

COMMENT ON COLUMN topo_podklady.tvm10_listoklad.lbl_vis
    IS 'Viditeľnosť popisky (viditeľná / neviditeľná).';

