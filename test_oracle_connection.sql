-- Script de test pour vérifier la configuration Oracle
-- À exécuter dans SQL*Plus ou SQL Developer

-- 1. Vérifier la structure de la table EMPLOYER
DESC EMPLOYER;

-- 2. Vérifier que la séquence SEQ_EMPLOYER existe
SELECT sequence_name, last_number 
FROM user_sequences 
WHERE sequence_name = 'SEQ_EMPLOYER';

-- 3. Compter les enregistrements
SELECT COUNT(*) as TOTAL_EMPLOYERS FROM EMPLOYER;

-- 4. Afficher tous les IDs existants
SELECT ID_EMP, FIRST_NAME, LAST_NAME, EMAIL 
FROM EMPLOYER 
ORDER BY ID_EMP;

-- 5. Test d'insertion manuelle (pour debug)
-- INSERT INTO EMPLOYER (ID_EMP, FIRST_NAME, LAST_NAME, EMAIL, PHONE, ROLE, PASSWORD, STATUS, HIRE_DATE)
-- VALUES (SEQ_EMPLOYER.NEXTVAL, 'Test', 'User', 'test@example.com', 123456789, 'Developer', 'password123', 'ACTIVE', SYSDATE);

-- 6. Test de sélection par ID (remplacer 1 par un ID existant)
-- SELECT * FROM EMPLOYER WHERE ID_EMP = 1;
