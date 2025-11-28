-- ============================================================================
-- ALTER TABLE SPONSORS - Add missing columns for DATE_DEBUT and DATE_FIN
-- ============================================================================

-- Add DATE_DEBUT column (Start date of sponsorship)
ALTER TABLE "ADMININSPIRASTUDIO"."SPONSORS" 
ADD "DATE_DEBUT" DATE DEFAULT SYSDATE;

-- Add DATE_FIN column (End date of sponsorship)
ALTER TABLE "ADMININSPIRASTUDIO"."SPONSORS" 
ADD "DATE_FIN" DATE;

-- ============================================================================
-- Verify the updated table structure
-- ============================================================================
DESCRIBE "ADMININSPIRASTUDIO"."SPONSORS";

-- Result should show:
-- ID_SPONSOR      NOT NULL NUMBER
-- NAME            NOT NULL VARCHAR2(50)
-- LAST_UPDATE     NOT NULL DATE
-- EMAIL           NOT NULL VARCHAR2(50)
-- STATUS          NOT NULL VARCHAR2(20)
-- DATE_DEBUT               DATE (NEW)
-- DATE_FIN                 DATE (NEW)
