***************************************************************************************
*     MONTE CARLO SIMULATION FOR MORPHORLOGY OF BLOCK POLYMER SEPERATION              *
*                           THREE DEMENSION IN LATTICE                                *   
*                               CREATED IN 2004,7                                     *
*       Z方向上有一块平板（模拟基片），另一接触面为空气。平板表面选择性吸附A或B链节   * 
*     NCHAIN- 高分子链的数目                                                          *
*     NBEAD - 高分子链长                                                              *
*     NBA   - 一条高分子链中链节A的数目                                               *
*     NBB   - 一条高分子链中链节B的数目                                               *
*     XC,YC,ZC- 空穴坐标                                                              *
*     INC   - 高分子链的序号                                                          *
*     INB   - 一条高分子链中链节的序号                                                *
*     IDUM  - 随机数发生器的种子数                                                    *
*     EKT   - THE PARAMETER OF BOLTZMAN                                               *
*     NPASS - 总的MC模拟步数                                                          *
*     NSKIP - 无热扰动步数                                                            *
*     NP    - MC模拟步数                                                              *
*     X,Y,Z - 链节的坐标                                                              *
*     ACT   - 链节间相互作用能                                                        *
***************************************************************************************
C    PROGRAM OF POLYMER MELT PHASE SEPERATION     
      IMPLICIT NONE
      INTEGER*4 NCHAIN,NBEAD,NCELL,NBA,NBB   
      INTEGER*4 LX,LY,LZ
      INTEGER*4 XC(25000),YC(25000),ZC(25000)
      INTEGER*4 X(25000,20),Y(25000,20),Z(25000,20)
	INTEGER*4 SX(25000,20),SY(25000,20),SZ(25000,20)
      INTEGER*4 INC(110,110,50),INB(110,110,50),I,J,K,IC
      INTEGER*4 NPASS,NSKIP,NP,NP1,SELE
	REAL ACT(2,2),WAACT,WBACT,VAACT,VBACT,EKT
      INTEGER  IDUM
      CHARACTER*12 H1,H2
C
      COMMON/POSITION/X,Y,Z
      COMMON/PO_CELL/XC,YC,ZC
      COMMON/OCCUPY/INC,INB
      COMMON/BEAD/NCHAIN,NBEAD
      COMMON/CELL/NCELL
      COMMON/PER_BEAD/NBA,NBB
      COMMON/NP/NP
      COMMON/CONTRAL/EKT
      COMMON/ACTION/ACT,WAACT,WBACT,VAACT,VBACT              
      COMMON/IDUM/IDUM
      COMMON/LATTICE/LX,LY,LZ 
      COMMON/TIME/NPASS,NSKIP  
C
      IDUM=-1000
     
C
      OPEN(1,FILE='INPUT.TXT',STATUS='OLD') 
      CALL READDATA     
      CLOSE(1)
	WRITE(*,*)"Make your selection."
	WRITE(*,*)"If you select 0, you will stop your programme."
	WRITE(*,*)"If you select 1, you will initize your programme."
	WRITE(*,*)"If you select 2, you will continue from last stop."
	READ(*,*)SELE
	IF(SELE.EQ.0)THEN
	   STOP 
	ELSE IF(SELE.EQ.1)THEN 
         NP1=1
	   DO I=1,LX
	      DO J=1,LY
	         DO K=1,LZ
	            INC(I,J,K)=0
	            INB(I,J,K)=0
               END DO
	      END DO
	   END DO
 	   CALL INIT 
C        调用初始化程序，用来给定模拟盒子内各高分子链节的初始位置。

         OPEN(5,FILE="LOCATION.TXT",STATUS="OLD")
         WRITE(5,*)"IDUM=",IDUM
         DO I=1,LX
		  DO J=1,LY
		     DO K=1,LZ
		    	WRITE(5,*)INC(I,J,K),INB(I,J,k)
			 END DO
		  END DO
	   END DO
	   CLOSE(5)		         
         WRITE(*,*)'COMPLETE INITIATION.'
C	   STOP
      ELSE IF(SELE.EQ.2)THEN
	   OPEN(5,FILE="LOCATION.TXT",STATUS="OLD")
         READ(5,*)H1,NP1
	   READ(5,*)H2,IDUM
         DO I=1,LX
	      DO J=1,LY
	         DO K=1,LZ
	            READ(5,*)INC(I,J,K),INB(I,J,K)
	            IF(INC(I,J,K).NE.0)THEN
				   X(INC(I,J,K),INB(I,J,K))=I
	               Y(INC(I,J,K),INB(I,J,K))=J
	               Z(INC(I,J,K),INB(I,J,K))=K
C	               WRITE(*,*)I,J,K
			    END IF
			 END DO
	      END DO
	   END DO
	   DO IC=1,NCELL
	      READ(5,*)XC(IC),YC(IC),ZC(IC)
         END DO
	   CLOSE(5)
	   WRITE(*,*)"READING IS OVER."
      END IF
	
C     开始循环运行MC模拟	      
      DO NP=NP1,NPASS
	   IF(NP.EQ.100.OR.NP.EQ.100000.OR.MOD(NP,500000).EQ.0)THEN
	      CALL EXAM
         END IF
C     执行检查程序，防止程序错误，导致高分子断链
	   IF(NP.EQ.(NP1+10).OR.NP.EQ.(NP1+100))THEN
	      WRITE(*,*)NP,"IS OK"
         END IF
         CALL EMPTY_CELL_MATHOD
C     调用MC模拟-键长涨落空穴扩散算法的子程序
         IF(NP.EQ.1.OR.NP.EQ.4.OR.NP.EQ.10)THEN
            WRITE(*,*)NP,'HAS PASSED'
         END IF 
C     以下调用画图子程序
         IF(NP.EQ.100.OR.MOD(NP,1000000).EQ.0)THEN
		  CALL GRAPH 
	   END IF
C     记录位置，为断电重算做准备
         IF(NP.EQ.100.OR.NP.EQ.10000.OR.MOD(NP,100000).EQ.0)THEN
	      WRITE(*,*) NP,"IS OK!"
            OPEN(5,FILE="LOCATION.TXT",STATUS="OLD")
	      WRITE(5,*)"NP=",NP
	      WRITE(5,*)"IDUM=",IDUM
	      DO I=1,LX
		     DO J=1,LY
			    DO K=1,LZ
			 	   WRITE(5,*)INC(I,J,K),INB(I,J,k)
				END DO
			 END DO
		  END DO
	      DO IC=1,NCELL
	         WRITE(5,*)XC(IC),YC(IC),ZC(IC)
            END DO
		  CLOSE(5)		         
	   END IF
C     记录最后一个构型
	IF(NP.GT.(NPASS-100000).AND.NP.LE.NPASS.AND.MOD(NP,500000).EQ.0) 
     $   THEN
	      OPEN(6,FILE="POSI.TXT",ACCESS="APPEND")
	      WRITE(6,*)"NP=",NP
	      DO I=1,LX
		     DO J=1,LY
			    DO K=1,LZ
			 	   WRITE(6,*)INC(I,J,K),INB(I,J,k)
				END DO
			 END DO
		  END DO
		  CLOSE(6)
      END IF 
      END DO
      END 
C
                            SUBROUTINE EXAM
***********************************************************************************
*                       EXAM CORRECTIVITY OF POSITION                             *
***********************************************************************************
      INTEGER*4 NCHAIN,NBEAD
      INTEGER*4 I,J,S,T
      INTEGER*4 X(25000,20),Y(25000,20),Z(25000,20)
	INTEGER*4 A1,A2,B1,B2,AA1,AA2,AA3,BB1,BB2,BB3,AB
      INTEGER*4 LX,LY,LZ

	COMMON/POSITION/X,Y,Z
	COMMON/BEAD/NCHAIN,NBEAD
      COMMON/LATTICE/LX,LY,LZ

	DO I=1,NCHAIN
	   DO J=1,NBEAD-1
            AA1=X(I,J)
	      AA2=Y(I,J)
	      AA3=Z(I,J)
	      BB1=X(I,J+1)
	      BB2=Y(I,J+1)
	      BB3=Z(I,J+1)
	      IF((AA1-BB1).GE.(LX-1))THEN
	         AA1=AA1-LX
	      ELSE IF((AA1-BB1).LE.(1-LX))THEN
	         AA1=AA1+LX
	      END IF
	      IF((AA2-BB2).GE.(LY-1))THEN
	         AA2=AA2-LY
	      ELSE IF((AA2-BB2).LE.(1-LY))THEN
	         AA2=AA2+LY
	      END IF
	      AB=(AA1-BB1)*(AA1-BB1)+(AA2-BB2)*(AA2-BB2)
     $		  +(AA3-BB3)*(AA3-BB3)
	      IF(AB.GT.2)THEN
	         WRITE(*,*) "LENGTH IS WRONG!"
	         STOP
	      END IF
		  IF(X(I,J).EQ.X(I,J+1).AND.Y(I,J).NE.Y(I,J+1)
     $   	    .AND.Z(I,J).NE.Z(I,J+1))THEN
	         A1=Y(I,J)
	         A2=Z(I,J)
		     B1=Y(I,J+1)
		     B2=Z(I,J+1)
		     DO S=1,NCHAIN
		        DO T=1,NBEAD-1
		           IF(X(I,J).EQ.X(S,T).AND.
     $			      A1.EQ.Y(S,T).AND.B2.EQ.Z(S,T)
     $                  .AND.B1.EQ.Y(S,T+1).AND.A2.EQ.Z(S,T+1))THEN
	                  WRITE(*,*) "IT IS WRONG!"
	                  WRITE(*,*) "I=",I,"J=",J
				      WRITE(*,*) "A1=",A1,"B2=",B2,"B1=",B1,"A2=",A2
	                  WRITE(*,*) "S=",S,"T=",T					  
				      WRITE(*,*) Y(S,T),Z(S,T),Y(S,T+1),Z(S,T+1)
				      STOP
                     END IF
	            END DO
	         END DO
            ELSE IF(Y(I,J).EQ.Y(I,J+1).AND.X(I,J).NE.X(I,J+1)
     $         .AND.Z(I,J).NE.Z(I,J+1))THEN
		     A1=X(I,J)
		     A2=Z(I,J)
		     B1=X(I,J+1)
		     B2=Z(I,J+1)
		     DO S=1,NCHAIN
		        DO T=1,NBEAD-1
		           IF(Y(I,J).EQ.Y(S,T).AND.
     $		    	  A1.EQ.X(S,T).AND.B2.EQ.Z(S,T)
     $                  .AND.B1.EQ.X(S,T+1).AND.A2.EQ.Z(S,T+1))THEN
	                  WRITE(*,*) "IT IS WRONG!"
	                  WRITE(*,*) "I=",I,"J=",J
					  WRITE(*,*) "A1=",A1,"B2=",B2,"B1=",B1,"A2=",A2
	                  WRITE(*,*) "S=",S,"T=",T					  
					  WRITE(*,*)  X(S,T),Z(S,T),X(S,T+1),Z(S,T+1)
	                  STOP
	               END IF
	            END DO
	         END DO
            ELSE IF(Z(I,J).EQ.Z(I,J+1).AND.X(I,J).NE.X(I,J+1)
     $         .AND.Y(I,J).NE.Y(I,J+1))THEN
		     A1=X(I,J)
		     A2=Y(I,J)
		     B1=X(I,J+1)
		     B2=Y(I,J+1)
		     DO S=1,NCHAIN
		        DO T=1,NBEAD-1
		           IF(Z(I,J).EQ.Z(S,T).AND.
     $		          A1.EQ.X(S,T).AND.B2.EQ.Y(S,T)
     $                  .AND.B1.EQ.X(S,T+1).AND.A2.EQ.Y(S,T+1))THEN
	                  WRITE(*,*) "IT IS WRONG!"
	                  WRITE(*,*)"S=",S,"T=",T,"C"
	                  WRITE(*,*)"I=",I,"J=",J
	                  STOP
	               END IF
	            END DO
	         END DO
	      END IF
	   END DO
	END DO			   
      RETURN
	END
	

	                SUBROUTINE GRAPH
***********************************************************************************
*                     THIS SUBROUTINE CALCULATE GRAPH POSITION                    *
***********************************************************************************
      IMPLICIT NONE
      INTEGER*4 NCHAIN,NBEAD,NCELL,NBA,NBB
	INTEGER*4 NP,NPASS,NSKIP   
      INTEGER*4 LX,LY,LZ
      INTEGER*4 XC(25000),YC(25000),ZC(25000)
      INTEGER*4 X(25000,20),Y(25000,20),Z(25000,20)
      INTEGER*4 INC(110,110,50),INB(110,110,50)
	INTEGER*4 WW,VV,RR
	INTEGER*4 TT,IA,IB
	 
      COMMON/POSITION/X,Y,Z
      COMMON/PO_CELL/XC,YC,ZC
      COMMON/OCCUPY/INC,INB
      COMMON/BEAD/NCHAIN,NBEAD
      COMMON/CELL/NCELL
      COMMON/PER_BEAD/NBA,NBB
      COMMON/NP/NP
      COMMON/LATTICE/LX,LY,LZ 
      COMMON/TIME/NPASS,NSKIP

	IF(NP.EQ.NPASS)THEN
	   OPEN(2,FILE='OUTPUT2.TXT',ACCESS='APPEND')
         DO RR=1,LZ
	      IA=0
	      IB=0
	      DO VV=1,LX
	         DO WW=1,LY
     	            IF(INC(VV,WW,RR).NE.0.AND.INB(VV,WW,RR)
     $		  .LE.NBA)     THEN
	            IA=IA+1
	            ELSE IF(INB(VV,WW,RR).GT.NBA.AND.INB(VV,WW,RR)
     $		.LE.NBEAD) THEN
                  IB=IB+1
	            END IF
	         CONTINUE
	         END DO
	      END DO
            WRITE(2,*) RR,IA,IB
	   END DO
	   CLOSE(2)
	END IF

	OPEN(3,FILE='OUTPUT1.TXT',ACCESS='APPEND')
      DO VV=1,LX
         DO WW=1,LY
            DO RR=1,LZ
            TT=0
            IF(INB(VV,WW,RR).EQ.0)THEN
               TT=0
            ELSEIF(INB(VV,WW,RR).LE.NBA.AND.INB(VV,WW,RR).GT.0)
     $      THEN
               TT=3
            ELSE IF(INB(VV,WW,RR).GT.NBA)THEN
               TT=5
            END IF
            WRITE(3,*) TT
            END DO
         END DO
      END DO  
	CLOSE(3)
	RETURN
	END    


	  
	                SUBROUTINE READDATA
***********************************************************************************
*                    THIS SUBOUTINE READS DATA FROM INPUT.IN FILE                 *
*                    ACT：A、B链节间的相互作用能                                  *
*                    WAACT：平板对A链节的作用能                                   *
*                    WBACT：平板对B链节的作用能                                   *
*                    VAACT: 空气对A链节的作用能                                   *
*                    VBACT: 空气对B链节的作用能                                   *
***********************************************************************************
	IMPLICIT NONE
      REAL ACT(2,2),WAACT,WBACT,VAACT,VBACT,EKT
	INTEGER*4 LX,LY,LZ
	INTEGER*4 NPASS,NSKIP
	INTEGER*4 NCHAIN,NBEAD,NCELL,NBA,NBB	

C
      COMMON/BEAD/NCHAIN,NBEAD
      COMMON/CELL/NCELL
      COMMON/PER_BEAD/NBA,NBB
      COMMON/CONTRAL/EKT
      COMMON/ACTION/ACT,WAACT,WBACT,VAACT,VBACT 
      COMMON/LATTICE/LX,LY,LZ
      COMMON/TIME/NPASS,NSKIP

C
C  READ THE LATTICE SIZE AND TEMPERATURE
C	  
	READ(1,*)NPASS,NSKIP
      READ(1,*)NCHAIN,NBEAD,NCELL,NBA,NBB
      READ(1,*)LX,LY,LZ
      READ(1,*)EKT 
	READ(1,*)ACT(1,1),ACT(1,2)
	READ(1,*)ACT(2,1),ACT(2,2)
      READ(1,*)WAACT,WBACT,VAACT,VBACT
	RETURN
	END
C
	                  SUBROUTINE INIT
***************************************************************************
*                INITIALIZE CHAIN AND BEAD POSITION  	                    *
***************************************************************************
      IMPLICIT NONE
      INTEGER*4 NCHAIN,NBEAD,NCELL,NBA,NBB   
      INTEGER*4 LX,LY,LZ
      INTEGER*4 XC(25000),YC(25000),ZC(25000)
      INTEGER*4 X(25000,20),Y(25000,20),Z(25000,20)
      INTEGER*4 INC(110,110,50),INB(110,110,50),I,J,K
      INTEGER*4 N,M,EE
      INTEGER   IDUM
      REAL RAN2
C
C
      COMMON/POSITION/X,Y,Z
      COMMON/PO_CELL/XC,YC,ZC
      COMMON/OCCUPY/INC,INB
      COMMON/BEAD/NCHAIN,NBEAD
      COMMON/CELL/NCELL
      COMMON/PER_BEAD/NBA,NBB
      COMMON/IDUM/IDUM
      COMMON/LATTICE/LX,LY,LZ 
C
C    EMPTY THE LATTICE FIRST
C      
      N=LZ
      M=NCHAIN/N
	EE=1
	DO EE=1,N
         I=M*(EE-1)+1
         DO I=M*(EE-1)+1,M*EE-M/2
            Y(I,1)=INT(RAN2(IDUM)*LY)+1
            IF(Y(I,1).EQ.0)THEN
               Y(I,1)=1
            ELSE IF(Y(I,1).EQ.(LY+1))THEN
               Y(I,1)=LY
            END IF
            J=1
            DO J=1,NBEAD
               X(I,J)=I-M*(EE-1)
               IF(J.GT.1)THEN
                  Y(I,J)=Y(I,J-1)+1
               END IF 
               Z(I,J)=EE
               CALL PERIOD(I,J) 
            END DO
            K=I
            XC(K)=I-M*(EE-1)
            YC(K)=Y(I,NBEAD)+1
            IF(YC(K).GT.LY)THEN
               YC(K)=YC(K)-LY
            END IF
            ZC(K)=EE
         END DO
         I=M*EE-M/2+1
	   DO I=M*EE-M/2+1,M*EE
            J=1
            DO J=1,NBEAD
               X(I,J)=I-(M*EE-M/2)
      	  	 Y(I,J)=Y(I-M/2,J)+NBEAD+1
               Z(I,J)=EE
               CALL PERIOD(I,J)
            END DO
            K=I
            XC(K)=I-(M*EE-M/2)
            YC(K)=Y(I,NBEAD)+1
            IF(YC(K).GT.LY)THEN
               YC(K)=YC(K)-LY
            END IF
            ZC(K)=EE
         END DO	    
	END DO
	I=1
      DO I=1,NCHAIN
	   J=1
         DO J=1,NBEAD
            INC(X(I,J),Y(I,J),Z(I,J))=I
            INB(X(I,J),Y(I,J),Z(I,J))=J
         END DO
	END DO
      RETURN
      END 


C
                        SUBROUTINE EMPTY_CELL_MATHOD
**************************************************************************
*                 THIS SUBROUTINE EXACUTES EMPTY CELL MATHOD             *
**************************************************************************
      IMPLICIT NONE
      INTEGER*4 NCELL
	INTEGER*4 IC
      INTEGER*4 IPCOUNT
      REAL IDUM,RAN2
C
      COMMON/CELL/NCELL
      COMMON/IDUM/IDUM
      
C
	DO IPCOUNT=1,NCELL
	  IC=INT(RAN2(IDUM)*NCELL-0.001)+1
	  IF(IC.GT.NCELL)THEN
	     IC=NCELL
	  END IF
	  CALL EXCHANGE(IC)
      END DO
	RETURN
	END 

	                  SUBROUTINE EXCHANGE(IC)
**************************************************************************
*               ATTEMP TO MOVE AND EXCHANGE COORDINATE                   *
*     ITXC,ITYC,ITZC-TEMPTARY COORDINATE OF CELL                         *
*     XPP,YPP,ZPP   -TEMPTARY COORDINATE OF BEAD                         * 
*     I1COUNT   -统计AB相邻的链节对数                                    * 
*     I2COUNT   -统计基片表面吸附A链节的数目                             * 
*     I3COUNT   -统计基片表面吸附B链节的数目                             * 
*     I4COUNT   -统计空气接触表面A链节的数目                             * 
*     I5COUNT   -统计空气接触表面B链节的数目                             * 
**************************************************************************
      IMPLICIT NONE
      INTEGER*4 NCHAIN,NBEAD,NCELL,NBA,NBB   
      INTEGER*4 LX,LY,LZ
      INTEGER*4 XC(25000),YC(25000),ZC(25000)
	INTEGER*4 ITXC,ITYC,ITZC
      INTEGER*4 X(25000,20),Y(25000,20),Z(25000,20)
	INTEGER*4 IXO,IYO,IZO,IXF,IYF,IZF,IXB,IYB,IZB
	INTEGER*4 IXOO,IYOO,IZOO,IXFF,IYFF,IZFF,IXBB,IYBB,IZBB
      INTEGER*4 INC(110,110,50),INB(110,110,50),I,J,K
      INTEGER*4 NPASS,NSKIP,NP
	INTEGER*4 I1COUNT,I2COUNT,I3COUNT,I4COUNT,I5COUNT
	INTEGER*4 IC
	REAL      EOLD,ENEW,ECHANGE
	INTEGER*4 IDL,IDM,IDN,IL,IM,IN,A1,A2,B1,B2,C1,C2,S1,S2
	INTEGER*4 KK,XPP(NBEAD),YPP(NBEAD),ZPP(NBEAD)
      REAL      ACT(2,2),WAACT,WBACT,VAACT,VBACT,EKT
	REAL      RAN2,RANDOM,RN
      INTEGER   IDUM

C
      COMMON/POSITION/X,Y,Z
      COMMON/PO_CELL/XC,YC,ZC
      COMMON/OCCUPY/INC,INB
      COMMON/BEAD/NCHAIN,NBEAD
      COMMON/CELL/NCELL
      COMMON/PER_BEAD/NBA,NBB
      COMMON/NP/NP
      COMMON/CONTRAL/EKT
      COMMON/ACTION/ACT,WAACT,WBACT,VAACT,VBACT
      COMMON/IDUM/IDUM
      COMMON/LATTICE/LX,LY,LZ 
      COMMON/TIME/NPASS,NSKIP      


C     SELECT EXCHANGE LATTICE IN RANDOM
      ITXC=XC(IC)
	ITYC=YC(IC)
	ITZC=ZC(IC)
10    CONTINUE
     
	   
      RANDOM=RAN2(IDUM)
	IF(RANDOM.LT.0.3333333333333333)THEN
	   IDL=-1
	ELSE IF(RANDOM.GT.0.6666666666666667)THEN
	   IDL=0
	ELSE
	   IDL=1
	END IF
      IL=ITXC+IDL
	
	RANDOM=RAN2(IDUM)
	IF(RANDOM.LT.0.3333333333333333)THEN
	   IDM=-1
	ELSE IF(RANDOM.GT.0.6666666666666667)THEN
	   IDM=0
	ELSE
	   IDM=1
	END IF
	IM=ITYC+IDM
	
90    CONTINUE
	IF(IDL.EQ.0.AND.IDM.EQ.0)THEN
	   RANDOM=RAN2(IDUM)
	   IF(RANDOM.LT.0.5)THEN
	      IDN=-1
	   ELSE
	      IDN=1
	   END IF
	ELSE IF(IABS(IDL).EQ.1.AND.IABS(IDM).EQ.1)THEN
	   IDN=0
	ELSE 
         RANDOM=RAN2(IDUM)
	   IF(RANDOM.LT.0.3333333333333333)THEN
	      IDN=1
	   ELSE IF(RANDOM.GT.0.6666666666666667)THEN
	      IDN=-1
         ELSE
	      IDN=0
	   END IF  
	END IF	
	IF(IABS(IDL).EQ.IABS(IDM).AND.IABS(IDL).EQ.IABS(IDN))THEN
	   WRITE(*,*)'IT IS WRONG!'
	   STOP
	END IF      
	IN=ITZC+IDN
	IF(IN.LT.1.OR.IN.GT.LZ)THEN
	   GOTO 90
	END IF
	
	IF(IL.GT.LX)THEN
	   IL=IL-LX
      ELSE IF(IL.LT.1)THEN
	   IL=IL+LX
      END IF
	IF(IM.GT.LY)THEN
	   IM=IM-LY
	ELSE IF(IM.LT.1)THEN
	   IM=IM+LY
      END IF
      
	I=INC(IL,IM,IN)
	J=INB(IL,IM,IN)
	IF(I.EQ.0)GOTO 21
C
	IF(J.GT.1.AND.J.LT.NBEAD)THEN
	   IXO=X(I,J)
	   IXOO=X(I,J)
	   IYO=Y(I,J)
	   IYOO=Y(I,J)
	   IZO=Z(I,J)
	   IZOO=Z(I,J)
	   IXB=X(I,J+1)
	   IXBB=X(I,J+1)
	   IYB=Y(I,J+1)
	   IYBB=Y(I,J+1)
	   IZB=Z(I,J+1)
	   IZBB=Z(I,J+1)
	   IXF=X(I,J-1)
	   IXFF=X(I,J-1)
	   IYF=Y(I,J-1)
	   IYFF=Y(I,J-1)
	   IZF=Z(I,J-1)
	   IZFF=Z(I,J-1)
	   IF(IABS(IXO-ITXC).GT.1)THEN
	      IF(ITXC.LT.2)THEN
	         IXO=IXO-LX
	      ELSE
	         IXO=IXO+LX
	      END IF
	   END IF
	   IF(IABS(IXO-IXB).GT.1)THEN
	      IF(IXO.LT.2)THEN
	         IXB=IXB-LX
	      ELSE 
	         IXB=IXB+LX
	      END IF
         END IF
	   IF(IABS(IXO-IXF).GT.1)THEN
	      IF(IXO.LT.2)THEN
	         IXF=IXF-LX
	      ELSE
	         IXF=IXF+LX
	      END IF
	   END IF
                   
	   IF(IABS(IYO-ITYC).GT.1)THEN
	      IF(ITYC.LT.2)THEN
	         IYO=IYO-LY
	      ELSE
	         IYO=IYO+LY
	      END IF
	   END IF
	   IF(IABS(IYO-IYB).GT.1)THEN
	      IF(IYO.LT.2)THEN
	         IYB=IYB-LY
	      ELSE 
	         IYB=IYB+LY
	      END IF
         END IF
	   IF(IABS(IYO-IYF).GT.1)THEN
	      IF(IYO.LT.2)THEN
	         IYF=IYF-LY
	      ELSE
	         IYF=IYF+LY
	      END IF
	   END IF

         A1=IABS(ITXC-IXB)
         B1=IABS(ITYC-IYB)
	   C1=IABS(ITZC-IZB)
	   S1=(A1*A1+B1*B1+C1*C1)
	   A2=IABS(ITXC-IXF)
	   B2=IABS(ITYC-IYF)
	   C2=IABS(ITZC-IZF)
	   S2=(A2*A2+B2*B2+C2*C2)
	   IF(NP.GT.NSKIP)THEN
	      IF(S1.LE.2.AND.S2.LE.2)THEN
 	         CALL ENERGY1(I1COUNT,I2COUNT,I3COUNT,I4COUNT,I5COUNT,I,J)
	         EOLD=I1COUNT*ACT(1,2)+I2COUNT*WAACT+I3COUNT*WBACT
     $		 +I4COUNT*VAACT+I5COUNT*VBACT
			 IF(S1.EQ.2.OR.S2.EQ.2)THEN
	            IF(ITXC.EQ.X(I,J).AND.
     $			  ITYC.NE.Y(I,J).AND.ITZC.NE.Z(I,J))THEN
	              IF(IABS(INB(ITXC,ITYC,Z(I,J))-INB(ITXC,Y(I,J),ITZC))
     $                  .EQ.1.AND.(INC(ITXC,ITYC,Z(I,J))
     $				  .EQ.INC(ITXC,Y(I,J),ITZC)))THEN
	                  GOTO 21
				   END IF
				ELSE IF(ITYC.EQ.Y(I,J).AND.
     $			  ITXC.NE.X(I,J).AND.ITZC.NE.Z(I,J))THEN
				  IF(IABS(INB(ITXC,ITYC,Z(I,J))-INB(X(I,J),ITYC,ITZC))
     $				  .EQ.1.AND.(INC(ITXC,ITYC,Z(I,J))
     $				  .EQ.INC(X(I,J),ITYC,ITZC)))THEN
                        GOTO 21
				  END IF
				ELSE IF(ITZC.EQ.Z(I,J).AND.
     $			  ITXC.NE.X(I,J).AND.ITXC.NE.X(I,J))THEN
	              IF(IABS(INB(X(I,J),ITYC,ITZC)-INB(ITXC,Y(I,J),ITZC))
     $				 .EQ.1.AND.(INC(X(I,J),ITYC,ITZC)
     $     			 .EQ.INC(ITXC,Y(I,J),ITZC)))THEN
	                  GOTO 21
                    END IF
	            END IF
	            IF(S1.EQ.2)THEN
	               IF(ITXC.EQ.X(I,J+1))THEN
	                 IF(IABS(INB(ITXC,ITYC,Z(I,J+1))-INB(ITXC,Y(I,J+1)
     $				    ,ITZC)).EQ.1.AND.(INC(ITXC,ITYC,Z(I,J+1))
     $                    .EQ.INC(ITXC,Y(I,J+1),ITZC)))THEN
	                     GOTO 21
	                 END IF
                     ELSE IF(ITYC.EQ.Y(I,J+1))THEN
	                 IF(IABS(INB(ITXC,ITYC,Z(I,J+1))-INB(X(I,J+1),ITYC
     $					,ITZC)).EQ.1.AND.(INC(ITXC,ITYC,Z(I,J+1))
     $                    .EQ.INC(X(I,J+1),ITYC,ITZC)))THEN
	                     GOTO 21
	                 END IF
                     ELSE IF(ITZC.EQ.Z(I,J+1))THEN
	                 IF(IABS(INB(ITXC,Y(I,J+1),ITZC)-INB(X(I,J+1),ITYC
     $					,ITZC)).EQ.1.AND.(INC(ITXC,Y(I,J+1),ITZC)
     $                    .EQ.INC(X(I,J+1),ITYC,ITZC)))THEN
	                     GOTO 21
	            	 END IF
     				   END IF
                  END IF
				IF(S2.EQ.2)THEN
				   IF(ITXC.EQ.X(I,J-1))THEN
	                 IF(IABS(INB(ITXC,ITYC,Z(I,J-1))-INB(ITXC,Y(I,J-1)
     $					,ITZC)).EQ.1.AND.(INC(ITXC,ITYC,Z(I,J-1))
     $                    .EQ.INC(ITXC,Y(I,J-1),ITZC)))THEN
	                    GOTO 21
	                 END IF
	               ELSE IF(ITYC.EQ.Y(I,J-1))THEN
	                 IF(IABS(INB(ITXC,ITYC,Z(I,J-1))-INB(X(I,J-1),ITYC
     $					,ITZC)).EQ.1.AND.(INC(ITXC,ITYC,Z(I,J-1))
     $                    .EQ.INC(X(I,J-1),ITYC,ITZC)))THEN
						GOTO 21
				     END IF
				   ELSE IF(ITZC.EQ.Z(I,J-1))THEN
	                 IF(IABS(INB(ITXC,Y(I,J-1),ITZC)-INB(X(I,J-1),ITYC
     $					,ITZC)).EQ.1.AND.(INC(ITXC,Y(I,J-1),ITZC)
     $                    .EQ.INC(X(I,J-1),ITYC,ITZC)))THEN
	                    GOTO 21
	                 END IF
	               END IF
	            END IF
			 END IF
		     XC(IC)=X(I,J)
	         YC(IC)=Y(I,J)
	         ZC(IC)=Z(I,J)
	         X(I,J)=ITXC
	         Y(I,J)=ITYC
	         Z(I,J)=ITZC
			 INC(X(I,J),Y(I,J),Z(I,J))=I
			 INB(X(I,J),Y(I,J),Z(I,J))=J
			 INC(XC(IC),YC(IC),ZC(IC))=0
			 INB(XC(IC),YC(IC),ZC(IC))=0
	         CALL ENERGY1(I1COUNT,I2COUNT,I3COUNT,I4COUNT,I5COUNT,I,J)
	         ENEW=I1COUNT*ACT(1,2)+I2COUNT*WAACT+I3COUNT*WBACT
     $		 +I4COUNT*VAACT+I5COUNT*VBACT
	         ECHANGE=ENEW-EOLD
	         IF(ECHANGE.GT.0)THEN
	            RN=RAN2(IDUM)
	            IF(RN.GT.EXP(-ECHANGE*EKT))THEN
	               X(I,J)=XC(IC)
	               Y(I,J)=YC(IC)
	               Z(I,J)=ZC(IC)
				   XC(IC)=ITXC
	               YC(IC)=ITYC
	               ZC(IC)=ITZC
	            END IF
	         END IF
			 INC(X(I,J),Y(I,J),Z(I,J))=I
			 INB(X(I,J),Y(I,J),Z(I,J))=J
			 INC(XC(IC),YC(IC),ZC(IC))=0
			 INB(XC(IC),YC(IC),ZC(IC))=0
		  END IF  
	   ELSE IF(NP.LE.NSKIP)THEN
	      IF(S1.LE.2.AND.S2.LE.2)THEN
	         IF(S1.EQ.2.OR.S2.EQ.2)THEN
	            IF(ITXC.EQ.IXOO.AND.
     $			   ITYC.NE.IYOO.AND.ITZC.NE.IZOO)THEN
	              IF(IABS(INB(ITXC,ITYC,Z(I,J))-INB(ITXC,Y(I,J),ITZC))
     $			   .EQ.1.AND.(INC(ITXC,ITYC,Z(I,J)).EQ.INC(ITXC,Y(I,J)
     $			   ,ITZC)))THEN
	                  GOTO 21
				   END IF
	            ELSE IF(ITYC.EQ.IYOO.AND.
     $			  ITXC.NE.IXOO.AND.ITZC.NE.IZOO)THEN
				  IF(IABS(INB(ITXC,ITYC,Z(I,J))-INB(X(I,J),ITYC,ITZC))
     $			   .EQ.1.AND.(INC(ITXC,ITYC,Z(I,J)).EQ.INC(X(I,J),ITYC
     $			   ,ITZC)))THEN
                        GOTO 21
				   END IF
	            ELSE IF(ITZC.EQ.IZOO.AND.
     $			  ITXC.NE.IXOO.AND.ITYC.NE.IYOO)THEN
	              IF(IABS(INB(X(I,J),ITYC,ITZC)-INB(ITXC,Y(I,J),ITZC))
     $			   .EQ.1.AND.(INC(X(I,J),ITYC,ITZC).EQ.INC(ITXC,Y(I,J)
     $			   ,ITZC)))THEN
	                  GOTO 21
                     END IF
	            END IF
	            IF(S1.EQ.2)THEN
	               IF(ITXC.EQ.X(I,J+1))THEN
	                 IF(IABS(INB(ITXC,ITYC,Z(I,J+1))-INB(ITXC,Y(I,J+1)
     $				  ,ITZC)).EQ.1.AND.(INC(ITXC,ITYC,Z(I,J+1))
     $                  .EQ.INC(ITXC,Y(I,J+1),ITZC)))THEN
	                     GOTO 21
	                  END IF
                     ELSE IF(ITYC.EQ.Y(I,J+1))THEN
	                 IF(IABS(INB(ITXC,ITYC,Z(I,J+1))-INB(X(I,J+1),ITYC
     $				  ,ITZC)).EQ.1.AND.(INC(ITXC,ITYC,Z(I,J+1))
     $                  .EQ.INC(X(I,J+1),ITYC,ITZC)))THEN
	                     GOTO 21
	                  END IF
                     ELSE IF(ITZC.EQ.Z(I,J+1))THEN
	                 IF(IABS(INB(ITXC,Y(I,J+1),ITZC)-INB(X(I,J+1),ITYC
     $				  ,ITZC)).EQ.1.AND.(INC(ITXC,Y(I,J+1),ITZC)
     $                  .EQ.INC(X(I,J+1),ITYC,ITZC)))THEN
	                     GOTO 21
	               	  END IF
     				   END IF
	            END IF
                  IF(S2.EQ.2)THEN
				   IF(ITXC.EQ.X(I,J-1))THEN
	                 IF(IABS(INB(ITXC,ITYC,Z(I,J-1))-INB(ITXC,Y(I,J-1)
     $				  ,ITZC)).EQ.1.AND.(INC(ITXC,ITYC,Z(I,J-1))
     $                  .EQ.INC(ITXC,Y(I,J-1),ITZC)))THEN
	                    GOTO 21
	                  END IF
	               ELSE IF(ITYC.EQ.Y(I,J-1))THEN
	                 IF(IABS(INB(ITXC,ITYC,Z(I,J-1))-INB(X(I,J-1),ITYC
     $				  ,ITZC)).EQ.1.AND.(INC(ITXC,ITYC,Z(I,J-1))
     $                  .EQ.INC(X(I,J-1),ITYC,ITZC)))THEN
						GOTO 21
					  END IF
				   ELSE IF(ITZC.EQ.Z(I,J-1))THEN
	                 IF(IABS(INB(ITXC,Y(I,J-1),ITZC)-INB(X(I,J-1),ITYC
     $				  ,ITZC)).EQ.1.AND.(INC(ITXC,Y(I,J-1),ITZC)
     $                  .EQ.INC(X(I,J-1),ITYC,ITZC)))THEN
	                    GOTO 21
	                  END IF
	               END IF
	            END IF
			 END IF
		     XC(IC)=X(I,J)
	         YC(IC)=Y(I,J)
	         ZC(IC)=Z(I,J)
	         X(I,J)=ITXC
	         Y(I,J)=ITYC
	         Z(I,J)=ITZC
	         INC(X(I,J),Y(I,J),Z(I,J))=I
			 INB(X(I,J),Y(I,J),Z(I,J))=J
			 INC(XC(IC),YC(IC),ZC(IC))=0
		     INB(XC(IC),YC(IC),ZC(IC))=0 
		  END IF
	   END IF
	ELSE IF (J.EQ.1)THEN
	  IXO=X(I,J)
	  IXOO=X(I,J)
	  IYO=Y(I,J)
	  IYOO=Y(I,J)
	  IZO=Z(I,J)
	  IZOO=Z(I,J)
	  IXB=X(I,J+1)
	  IXBB=X(I,J+1)
        IYB=Y(I,J+1)
	  IYBB=Y(I,J+1)
        IZB=Z(I,J+1)
	  IZBB=Z(I,J+1)
	  IF(IABS(IXO-ITXC).GT.1)THEN
          IF(ITXC.LT.2)THEN
	      IXO=IXO-LX
          ELSE 
	      IXO=IXO+LX
	    ENDIF
	  ENDIF
	  IF(IABS(IXO-IXB).GT.1)THEN
          IF(IXO.LT.2)THEN
	      IXB=IXB-LX
          ELSE 
	      IXB=IXB+LX
	    ENDIF
	  ENDIF
	  IF(IABS(IYO-ITYC).GT.1)THEN
          IF(ITYC.LT.2)THEN
	      IYO=IYO-LY
          ELSE
	      IYO=IYO+LY
	    ENDIF
	  ENDIF
	  IF(IABS(IYO-IYB).GT.1)THEN
          IF(IYO.LT.2)THEN
	      IYB=IYB-LY
          ELSE 
	      IYB=IYB+LY
	    ENDIF
	  ENDIF
 
        A1=IABS(ITXC-IXB)
	  B1=IABS(ITYC-IYB)
	  C1=IABS(ITZC-IZB)
	  S1=(A1*A1+B1*B1+C1*C1)
	  IF(NP.GT.NSKIP)THEN 	
	     IF(S1.LE.2)THEN
     	        CALL ENERGY2(I1COUNT,I2COUNT,I4COUNT,I,J)
	        EOLD=I1COUNT*ACT(1,2)+I2COUNT*WAACT+I4COUNT*VAACT
	        IF(S1.EQ.2)THEN
			   IF(ITXC.EQ.X(I,J))THEN
	              IF(IABS(INB(ITXC,ITYC,Z(I,J))-INB(ITXC,Y(I,J),ITZC))
     $			  .EQ.1.AND.(INC(ITXC,ITYC,Z(I,J))
     $              .EQ.INC(ITXC,Y(I,J),ITZC)))THEN
	                 GOTO 21
	     	      END IF
			   ELSE IF(ITYC.EQ.Y(I,J))THEN
			      IF(IABS(INB(ITXC,ITYC,Z(I,J))-INB(X(I,J),ITYC,ITZC))
     $			  .EQ.1.AND.(INC(ITXC,ITYC,Z(I,J))
     $              .EQ.INC(X(I,J),ITYC,ITZC)))THEN
                       GOTO 21
			      END IF
			   ELSE IF(ITZC.EQ.Z(I,J))THEN
	              IF(IABS(INB(X(I,J),ITYC,ITZC)-INB(ITXC,Y(I,J),ITZC))
     $			  .EQ.1.AND.(INC(X(I,J),ITYC,ITZC)
     $              .EQ.INC(ITXC,Y(I,J),ITZC)))THEN
	                 GOTO 21
                    END IF
	           END IF
	           IF(ITXC.EQ.X(I,J+1))THEN
	              IF(IABS(INB(ITXC,ITYC,Z(I,J+1))-INB(ITXC,Y(I,J+1)
     $			  ,ITZC)).EQ.1.AND.(INC(ITXC,ITYC,Z(I,J+1))
     $              .EQ.INC(ITXC,Y(I,J+1),ITZC)))THEN
	                 GOTO 21
	              END IF
                 ELSE IF(ITYC.EQ.Y(I,J+1))THEN
	              IF(IABS(INB(ITXC,ITYC,Z(I,J+1))-INB(X(I,J+1),ITYC
     $			  ,ITZC)).EQ.1.AND.(INC(ITXC,ITYC,Z(I,J+1))
     $              .EQ.INC(X(I,J+1),ITYC,ITZC)))THEN
	                 GOTO 21
	              END IF
                 ELSE IF(ITZC.EQ.Z(I,J+1))THEN
	              IF(IABS(INB(ITXC,Y(I,J+1),ITZC)-INB(X(I,J+1),ITYC
     $			  ,ITZC)).EQ.1.AND.(INC(ITXC,Y(I,J+1),ITZC)
     $              .EQ.INC(X(I,J+1),ITYC,ITZC)))THEN
	                 GOTO 21
	              END IF
     			   END IF
	        END IF    
		    XC(IC)=X(I,J)
	        YC(IC)=Y(I,J)
	        ZC(IC)=Z(I,J)
	        X(I,J)=ITXC
	        Y(I,J)=ITYC
	        Z(I,J)=ITZC
	        INC(X(I,J),Y(I,J),Z(I,J))=I
      		INB(X(I,J),Y(I,J),Z(I,J))=J
		    INC(XC(IC),YC(IC),ZC(IC))=0
			INB(XC(IC),YC(IC),ZC(IC))=0
     	        CALL ENERGY2(I1COUNT,I2COUNT,I4COUNT,I,J)
	        ENEW=I1COUNT*ACT(1,2)+I2COUNT*WAACT+I4COUNT*VAACT
	        ECHANGE=ENEW-EOLD
	        IF(ECHANGE.GT.0)THEN
	           RN=RAN2(IDUM)
	           IF(RN.GT.EXP(-ECHANGE*EKT))THEN
	              X(I,J)=XC(IC)
	              Y(I,J)=YC(IC)
	              Z(I,J)=ZC(IC)
			      XC(IC)=ITXC
	              YC(IC)=ITYC
	              ZC(IC)=ITZC
	           END IF
	        END IF
		    INC(X(I,J),Y(I,J),Z(I,J))=I
		    INB(X(I,J),Y(I,J),Z(I,J))=J
		    INC(XC(IC),YC(IC),ZC(IC))=0
		    INB(XC(IC),YC(IC),ZC(IC))=0
	     ELSE IF(S1.GT.2)THEN
     	        CALL ENERGY3(I1COUNT,I2COUNT,I3COUNT,I4COUNT,I5COUNT,I)
	        EOLD=I1COUNT*ACT(1,2)+I2COUNT*WAACT+I3COUNT*WBACT
     $		 +I4COUNT*VAACT+I5COUNT*VBACT
              DO KK=1,NBEAD
	           XPP(KK)=X(I,KK)
	           YPP(KK)=Y(I,KK)
	           ZPP(KK)=Z(I,KK)
	        END DO
	        IF(ITXC.EQ.IXOO.AND.
     $		   ITYC.NE.IYOO.AND.ITZC.NE.IZOO)THEN
	           IF(IABS(INB(ITXC,ITYC,IZOO)-INB(ITXC,IYOO,ITZC)).EQ.1
     $              .AND.(INC(ITXC,ITYC,IZOO).EQ.INC(ITXC,IYOO,ITZC)))
     $              THEN
	              GOTO 21
                 END IF
	        ELSE IF(ITYC.EQ.IYOO.AND.
     $		   ITXC.NE.IXOO.AND.ITZC.NE.IZOO)THEN
	           IF(IABS(INB(ITXC,ITYC,IZOO)-INB(IXOO,ITYC,ITZC)).EQ.1
     $	          .AND.(INC(ITXC,ITYC,IZOO).EQ.INC(IXOO,ITYC,ITZC)))
     $              THEN
	              GOTO 21
	           END IF
	        ELSE IF(ITZC.EQ.IZOO.AND.
     $		   ITXC.NE.IXOO.AND.ITYC.NE.IYOO)THEN
	           IF(IABS(INB(ITXC,IYOO,ITZC)-INB(IXOO,ITYC,ITZC)).EQ.1
     $              .AND.(INC(ITXC,IYOO,ITZC).EQ.INC(IXOO,ITYC,ITZC)))
     $              THEN
	              GOTO 21
                 END IF
	        END IF
	        XC(IC)=XPP(NBEAD)
	        YC(IC)=YPP(NBEAD)
	        ZC(IC)=ZPP(NBEAD)
	        DO KK=2,NBEAD
	           X(I,KK)=XPP(KK-1)
	           Y(I,KK)=YPP(KK-1)
	           Z(I,KK)=ZPP(KK-1)
	           INC(X(I,KK),Y(I,KK),Z(I,KK))=I
	           INB(X(I,KK),Y(I,KK),Z(I,KK))=KK
		    END DO
	        X(I,1)=ITXC
	        Y(I,1)=ITYC
	        Z(I,1)=ITZC
              INC(X(I,1),Y(I,1),Z(I,1))=I
	        INB(X(I,1),Y(I,1),Z(I,1))=1
	        INC(XC(IC),YC(IC),ZC(IC))=0
	        INB(XC(IC),YC(IC),ZC(IC))=0	 
     	        CALL ENERGY3(I1COUNT,I2COUNT,I3COUNT,I4COUNT,I5COUNT,I)
			ENEW=I1COUNT*ACT(1,2)+I2COUNT*WAACT+I3COUNT*WBACT
     $		 +I4COUNT*VAACT+I5COUNT*VBACT
			ECHANGE=ENEW-EOLD
	        RN=RAN2(IDUM)
	        IF(ECHANGE.GT.0.AND.RN.GT.EXP(-ECHANGE*EKT))THEN
	           XC(IC)=ITXC
			   YC(IC)=ITYC
			   ZC(IC)=ITZC
	           INC(XC(IC),YC(IC),ZC(IC))=0
	           INB(XC(IC),YC(IC),ZC(IC))=0
			   DO KK=1,NBEAD 
			      X(I,KK)=XPP(KK)
				  Y(I,KK)=YPP(KK)
				  Z(I,KK)=ZPP(KK)
				  INC(X(I,KK),Y(I,KK),Z(I,KK))=I
				  INB(X(I,KK),Y(I,KK),Z(I,KK))=KK
			   END DO
			END IF	 			    
	     END IF	 
	  ELSE IF(NP.LE.NSKIP)THEN
	     IF(S1.LE.2)THEN
	        IF(S1.EQ.2)THEN
	           IF(ITXC.EQ.IXOO.AND.
     $			  ITYC.NE.IYOO.AND.ITZC.NE.IZOO)THEN
	              IF(IABS(INB(ITXC,ITYC,Z(I,J))-INB(ITXC,Y(I,J),ITZC))
     $			  .EQ.1.AND.(INC(ITXC,ITYC,Z(I,J)).EQ.INC(ITXC,Y(I,J)
     $			  ,ITZC)))THEN
	                 GOTO 21
	     	      END IF
	           ELSE IF(ITYC.EQ.IYOO.AND.
     $			  ITXC.NE.IXOO.AND.ITZC.NE.IZOO)THEN
			      IF(IABS(INB(ITXC,ITYC,Z(I,J))-INB(X(I,J),ITYC,ITZC))
     $			  .EQ.1.AND.(INC(ITXC,ITYC,Z(I,J)).EQ.INC(X(I,J),ITYC
     $              ,ITZC)))THEN
                       GOTO 21
			      END IF
	           ELSE IF(ITZC.EQ.IZOO.AND.
     $			  ITXC.NE.IXOO.AND.ITYC.NE.IYOO)THEN
	              IF(IABS(INB(X(I,J),ITYC,ITZC)-INB(ITXC,Y(I,J),ITZC))
     $			  .EQ.1.AND.(INC(X(I,J),ITYC,ITZC).EQ.INC(ITXC,Y(I,J)
     $              ,ITZC)))THEN
	                 GOTO 21
                    END IF
	           END IF
	           IF(ITXC.EQ.X(I,J+1))THEN
	              IF(IABS(INB(ITXC,ITYC,Z(I,J+1))-INB(ITXC,Y(I,J+1)
     $			  ,ITZC)).EQ.1.AND.(INC(ITXC,ITYC,Z(I,J+1))
     $              .EQ.INC(ITXC,Y(I,J+1),ITZC)))THEN
	                 GOTO 21
	              END IF
                 ELSE IF(ITYC.EQ.Y(I,J+1))THEN
	              IF(IABS(INB(ITXC,ITYC,Z(I,J+1))-INB(X(I,J+1),ITYC
     $			  ,ITZC)).EQ.1.AND.(INC(ITXC,ITYC,Z(I,J+1))
     $              .EQ.INC(X(I,J+1),ITYC,ITZC)))THEN
	                 GOTO 21
	              END IF
                 ELSE IF(ITZC.EQ.Z(I,J+1))THEN
	              IF(IABS(INB(ITXC,Y(I,J+1),ITZC)-INB(X(I,J+1),ITYC
     $			  ,ITZC)).EQ.1.AND.(INC(ITXC,Y(I,J+1),ITZC)
     $              .EQ.INC(X(I,J+1),ITYC,ITZC)))THEN
	                 GOTO 21
	              END IF
     			   END IF
	        END IF    
		    XC(IC)=X(I,J)
	        YC(IC)=Y(I,J)
	        ZC(IC)=Z(I,J)
	        X(I,J)=ITXC
	        Y(I,J)=ITYC
	        Z(I,J)=ITZC
	        INC(X(I,J),Y(I,J),Z(I,J))=I
      		INB(X(I,J),Y(I,J),Z(I,J))=J
		    INC(XC(IC),YC(IC),ZC(IC))=0
	  	 	INB(XC(IC),YC(IC),ZC(IC))=0                 
	     ELSE IF(S1.GT.2)THEN
              DO KK=1,NBEAD
	           XPP(KK)=X(I,KK)
	           YPP(KK)=Y(I,KK)
	           ZPP(KK)=Z(I,KK)
	        END DO
	        IF(ITXC.EQ.IXOO.AND.
     $		   ITYC.NE.IYOO.AND.ITZC.NE.IZOO)THEN
	           IF(IABS(INB(ITXC,ITYC,IZOO)-INB(ITXC,IYOO,ITZC)).EQ.1
     $           .AND.(INC(ITXC,ITYC,IZOO).EQ.INC(ITXC,IYOO,ITZC)))
     $           THEN
	              GOTO 21
                 END IF
	        ELSE IF(ITYC.EQ.IYOO.AND.
     $	       ITXC.NE.IXOO.AND.ITZC.NE.IZOO)THEN
	           IF(IABS(INB(ITXC,ITYC,IZOO)-INB(IXOO,ITYC,ITZC)).EQ.1
     $	       .AND.(INC(ITXC,ITYC,IZOO).EQ.INC(IXOO,ITYC,ITZC)))
     $           THEN
	              GOTO 21
	           END IF
	        ELSE IF(ITZC.EQ.IZOO.AND.
     $		   ITXC.NE.IXOO.AND.ITYC.NE.IYOO)THEN
	           IF(IABS(INB(ITXC,IYOO,ITZC)-INB(IXOO,ITYC,ITZC)).EQ.1
     $           .AND.(INC(ITXC,IYOO,ITZC).EQ.INC(IXOO,ITYC,ITZC)))
     $           THEN
	              GOTO 21
                 END IF
	        END IF
	        XC(IC)=XPP(NBEAD)
	        YC(IC)=YPP(NBEAD)
	        ZC(IC)=ZPP(NBEAD)
	        DO KK=2,NBEAD
	           X(I,KK)=XPP(KK-1)
	           Y(I,KK)=YPP(KK-1)
	           Z(I,KK)=ZPP(KK-1)
	           INC(X(I,KK),Y(I,KK),Z(I,KK))=I
	           INB(X(I,KK),Y(I,KK),Z(I,KK))=KK
		    END DO
	        X(I,1)=ITXC
	        Y(I,1)=ITYC
	        Z(I,1)=ITZC
              INC(X(I,1),Y(I,1),Z(I,1))=I
	        INB(X(I,1),Y(I,1),Z(I,1))=1
	        INC(XC(IC),YC(IC),ZC(IC))=0
	        INB(XC(IC),YC(IC),ZC(IC))=0	      
	     END IF
        END IF
	ELSE IF(J.EQ.NBEAD)THEN
	  IXO=X(I,J)
	  IXOO=X(I,J)
	  IYO=Y(I,J)
	  IYOO=Y(I,J)
	  IZO=Z(I,J)
	  IZOO=Z(I,J)
	  IXF=X(I,J-1)
	  IXFF=X(I,J-1)
        IYF=Y(I,J-1)
	  IYFF=Y(I,J-1)
        IZF=Z(I,J-1)
	  IZFF=Z(I,J-1)
	  IF(IABS(IXO-ITXC).GT.1)THEN
          IF(ITXC.LT.2)THEN
	      IXO=IXO-LX
          ELSE 
	      IXO=IXO+LX
	    ENDIF
	  ENDIF
	  IF(IABS(IXO-IXF).GT.1)THEN
          IF(IXO.LT.2)THEN
	      IXF=IXF-LX
          ELSE 
	      IXF=IXF+LX
	    ENDIF
	  ENDIF
	  IF(IABS(IYO-ITYC).GT.1)THEN
          IF(ITYC.LT.2)THEN
	      IYO=IYO-LY
          ELSE
	      IYO=IYO+LY
	    ENDIF
	  ENDIF
	  IF(IABS(IYO-IYF).GT.1)THEN
          IF(IYO.LT.2)THEN
	      IYF=IYF-LY
          ELSE 
	      IYF=IYF+LY
	    ENDIF
	  ENDIF

        A2=IABS(ITXC-IXF)
	  B2=IABS(ITYC-IYF)
	  C2=IABS(ITZC-IZF)
	  S2=(A2*A2+B2*B2+C2*C2)
	  IF(NP.GT.NSKIP)THEN
	     IF(S2.LE.2)THEN
      	    CALL ENERGY4(I1COUNT,I3COUNT,I5COUNT,I,J)
		    EOLD=I1COUNT*ACT(1,2)+I3COUNT*WBACT+I5COUNT*VBACT
	        IF(S2.EQ.2)THEN
	           IF(ITXC.EQ.IXOO.AND.
     $			  ITYC.NE.IYOO.AND.ITZC.NE.IZOO)THEN
	              IF(IABS(INB(ITXC,ITYC,Z(I,J))-INB(ITXC,Y(I,J),ITZC))
     $			  .EQ.1.AND.(INC(ITXC,ITYC,Z(I,J)).EQ.INC(ITXC,Y(I,J)
     $              ,ITZC)))THEN
	                 GOTO 21
	     	      END IF
	           ELSE IF(ITYC.EQ.IYOO.AND.
     $			  ITXC.NE.IXOO.AND.ITZC.NE.IZOO)THEN
			      IF(IABS(INB(ITXC,ITYC,Z(I,J))-INB(X(I,J),ITYC,ITZC))
     $			  .EQ.1.AND.(INC(ITXC,ITYC,Z(I,J)).EQ.INC(X(I,J),ITYC
     $              ,ITZC)))THEN
                       GOTO 21
			      END IF
	           ELSE IF(ITZC.EQ.IZOO.AND.
     $			  ITXC.NE.IXOO.AND.ITYC.NE.IYOO)THEN
	              IF(IABS(INB(X(I,J),ITYC,ITZC)-INB(ITXC,Y(I,J),ITZC))
     $			  .EQ.1.AND.(INC(X(I,J),ITYC,ITZC).EQ.INC(ITXC,Y(I,J)
     $              ,ITZC)))THEN
	                 GOTO 21
                    END IF
	           END IF
	           IF(ITXC.EQ.X(I,J-1))THEN
	              IF(IABS(INB(ITXC,ITYC,Z(I,J-1))-INB(ITXC,Y(I,J-1)
     $			  ,ITZC)).EQ.1.AND.(INC(ITXC,ITYC,Z(I,J-1))
     $              .EQ.INC(ITXC,Y(I,J-1),ITZC)))THEN
	                 GOTO 21
	              END IF
                 ELSE IF(ITYC.EQ.Y(I,J-1))THEN
	              IF(IABS(INB(ITXC,ITYC,Z(I,J-1))-INB(X(I,J-1),ITYC
     $			  ,ITZC)).EQ.1.AND.(INC(ITXC,ITYC,Z(I,J-1))
     $              .EQ.INC(X(I,J-1),ITYC,ITZC)))THEN
	                 GOTO 21
	              END IF
                 ELSE IF(ITZC.EQ.Z(I,J-1))THEN
	              IF(IABS(INB(ITXC,Y(I,J-1),ITZC)-INB(X(I,J-1),ITYC
     $			  ,ITZC)).EQ.1.AND.(INC(ITXC,Y(I,J-1),ITZC)
     $              .EQ.INC(X(I,J-1),ITYC,ITZC)))THEN
	                 GOTO 21
	              END IF
     			   END IF
	        END IF    
		    XC(IC)=X(I,J)
	        YC(IC)=Y(I,J)
	        ZC(IC)=Z(I,J)
	        X(I,J)=ITXC
	        Y(I,J)=ITYC
	        Z(I,J)=ITZC
	        INC(X(I,J),Y(I,J),Z(I,J))=I
      		INB(X(I,J),Y(I,J),Z(I,J))=J
		    INC(XC(IC),YC(IC),ZC(IC))=0
			INB(XC(IC),YC(IC),ZC(IC))=0
      	    CALL ENERGY4(I1COUNT,I3COUNT,I5COUNT,I,J)
	        ENEW=I1COUNT*ACT(1,2)+I3COUNT*WBACT+I5COUNT*VBACT
	        ECHANGE=ENEW-EOLD
	        IF(ECHANGE.GT.0)THEN
	           RN=RAN2(IDUM)
	           IF(RN.GT.EXP(-ECHANGE*EKT))THEN
	              X(I,J)=XC(IC)
	              Y(I,J)=YC(IC)
	              Z(I,J)=ZC(IC)
			      XC(IC)=ITXC
	              YC(IC)=ITYC
	              ZC(IC)=ITZC
	           END IF
	        END IF
		    INC(X(I,J),Y(I,J),Z(I,J))=I
		    INB(X(I,J),Y(I,J),Z(I,J))=J
		    INC(XC(IC),YC(IC),ZC(IC))=0
		    INB(XC(IC),YC(IC),ZC(IC))=0
	     ELSE IF(S2.GT.2)THEN
      	    CALL ENERGY3(I1COUNT,I2COUNT,I3COUNT,I4COUNT,I5COUNT,I)
	        EOLD=I1COUNT*ACT(1,2)+I2COUNT*WAACT+I3COUNT*WBACT
     $		 +I4COUNT*VAACT+I5COUNT*VBACT
			DO KK=1,NBEAD
	           XPP(KK)=X(I,KK)
                 YPP(KK)=Y(I,KK)
                 ZPP(KK)=Z(I,KK)
	        END DO
	        IF(ITXC.EQ.IXOO.AND.
     $		   ITYC.NE.IYOO.AND.ITZC.NE.IZOO)THEN
	           IF(IABS(INB(ITXC,ITYC,IZOO)-INB(ITXC,IYOO,ITZC)).EQ.1
     $              .AND.(INC(ITXC,ITYC,IZOO).EQ.INC(ITXC,IYOO,ITZC)))
     $              THEN
	              GOTO 21
                 END IF
	        ELSE IF(ITYC.EQ.IYOO.AND.
     $		   ITXC.NE.IXOO.AND.ITZC.NE.IZOO)THEN
	           IF(IABS(INB(ITXC,ITYC,IZOO)-INB(IXOO,ITYC,ITZC)).EQ.1
     $	          .AND.(INC(ITXC,ITYC,IZOO).EQ.INC(IXOO,ITYC,ITZC)))
     $              THEN
	              GOTO 21
	           END IF
	        ELSE IF(ITZC.EQ.IZOO.AND.
     $		   ITXC.NE.IXOO.AND.ITYC.NE.IYOO)THEN
	           IF(IABS(INB(ITXC,IYOO,ITZC)-INB(IXOO,ITYC,ITZC)).EQ.1
     $              .AND.(INC(ITXC,IYOO,ITZC).EQ.INC(IXOO,ITYC,ITZC)))
     $              THEN
	              GOTO 21
                 END IF
	        END IF
	        XC(IC)=XPP(1)
	        YC(IC)=YPP(1)
	        ZC(IC)=ZPP(1)
	        DO KK=1,NBEAD-1
	           X(I,KK)=XPP(KK+1)
	           Y(I,KK)=YPP(KK+1)
	           Z(I,KK)=ZPP(KK+1)
	           INC(X(I,KK),Y(I,KK),Z(I,KK))=I
	           INB(X(I,KK),Y(I,KK),Z(I,KK))=KK
     	        END DO
	        X(I,NBEAD)=ITXC
	        Y(I,NBEAD)=ITYC
	        Z(I,NBEAD)=ITZC
              INC(X(I,NBEAD),Y(I,NBEAD),Z(I,NBEAD))=I
	        INB(X(I,NBEAD),Y(I,NBEAD),Z(I,NBEAD))=NBEAD
	        INC(XC(IC),YC(IC),ZC(IC))=0
	        INB(XC(IC),YC(IC),ZC(IC))=0	         
	        CALL ENERGY3(I1COUNT,I2COUNT,I3COUNT,I4COUNT,I5COUNT,I)
	        ENEW=I1COUNT*ACT(1,2)+I2COUNT*WAACT+I3COUNT*WBACT
     $		 +I4COUNT*VAACT+I5COUNT*VBACT
	        ECHANGE=ENEW-EOLD
	        RN=RAN2(IDUM)
 	        IF(ECHANGE.GT.0.AND.RN.GT.EXP(-ECHANGE*EKT))THEN
	           XC(IC)=ITXC
	           YC(IC)=ITYC
	           ZC(IC)=ITZC
	           INC(XC(IC),YC(IC),ZC(IC))=0
	           INB(XC(IC),YC(IC),ZC(IC))=0
		       DO KK=1,NBEAD
	              X(I,KK)=XPP(KK)
	              Y(I,KK)=YPP(KK)
	              Z(I,KK)=ZPP(KK)
	              INC(X(I,KK),Y(I,KK),Z(I,KK))=I
	              INB(X(I,KK),Y(I,KK),Z(I,KK))=KK
	           END DO
              END IF
		 END IF  
	  ELSE IF(NP.LE.NSKIP)THEN
	     IF(S2.LE.2)THEN
	        IF(S2.EQ.2)THEN
	           IF(ITXC.EQ.IXOO.AND.
     $			  ITYC.NE.IYOO.AND.ITZC.NE.IZOO)THEN
	              IF(IABS(INB(ITXC,ITYC,Z(I,J))-INB(ITXC,Y(I,J),ITZC))
     $			  .EQ.1.AND.(INC(ITXC,ITYC,Z(I,J)).EQ.INC(ITXC,Y(I,J)
     $              ,ITZC)))THEN
	                 GOTO 21
	     	      END IF
	           ELSE IF(ITYC.EQ.IYOO.AND.
     $			  ITXC.NE.IXOO.AND.ITZC.NE.IZOO)THEN
			      IF(IABS(INB(ITXC,ITYC,Z(I,J))-INB(X(I,J),ITYC,ITZC))
     $			  .EQ.1.AND.(INC(ITXC,ITYC,Z(I,J)).EQ.INC(X(I,J),ITYC
     $              ,ITZC)))THEN
                       GOTO 21
			      END IF
	           ELSE IF(ITZC.EQ.IZOO.AND.
     $			  ITXC.NE.IXOO.AND.ITYC.NE.IYOO)THEN
	              IF(IABS(INB(X(I,J),ITYC,ITZC)-INB(ITXC,Y(I,J),ITZC))
     $			  .EQ.1.AND.(INC(X(I,J),ITYC,ITZC).EQ.INC(ITXC,Y(I,J)
     $              ,ITZC)))THEN
	                 GOTO 21
                    END IF
	           END IF
	           IF(ITXC.EQ.X(I,J-1))THEN
	              IF(IABS(INB(ITXC,ITYC,Z(I,J-1))-INB(ITXC,Y(I,J-1)
     $			  ,ITZC)).EQ.1.AND.(INC(ITXC,ITYC,Z(I,J-1))
     $              .EQ.INC(ITXC,Y(I,J-1),ITZC)))THEN
	                 GOTO 21
	              END IF
                 ELSE IF(ITYC.EQ.Y(I,J-1))THEN
	              IF(IABS(INB(ITXC,ITYC,Z(I,J-1))-INB(X(I,J-1),ITYC
     $			  ,ITZC)).EQ.1.AND.(INC(ITXC,ITYC,Z(I,J-1))
     $              .EQ.INC(X(I,J-1),ITYC,ITZC)))THEN
	                 GOTO 21
	              END IF
                 ELSE IF(ITZC.EQ.Z(I,J-1))THEN
	              IF(IABS(INB(ITXC,Y(I,J-1),ITZC)-INB(X(I,J-1),ITYC
     $			  ,ITZC)).EQ.1.AND.(INC(ITXC,Y(I,J-1),ITZC)
     $              .EQ.INC(X(I,J-1),ITYC,ITZC)))THEN
	                 GOTO 21
	              END IF
     			   END IF
	        END IF    
		    XC(IC)=X(I,J)
	        YC(IC)=Y(I,J)
	        ZC(IC)=Z(I,J)
	        X(I,J)=ITXC
	        Y(I,J)=ITYC
	        Z(I,J)=ITZC
	        INC(X(I,J),Y(I,J),Z(I,J))=I
      		INB(X(I,J),Y(I,J),Z(I,J))=J
		    INC(XC(IC),YC(IC),ZC(IC))=0
	   		INB(XC(IC),YC(IC),ZC(IC))=0
  	     ELSE IF(S2.GT.2)THEN
	        DO KK=1,NBEAD
	           XPP(KK)=X(I,KK)
                 YPP(KK)=Y(I,KK)
                 ZPP(KK)=Z(I,KK)
	        END DO
	        IF(ITXC.EQ.IXOO.AND.
     $	       ITYC.NE.IYOO.AND.ITZC.NE.IZOO)THEN
	           IF(IABS(INB(ITXC,ITYC,IZOO)-INB(ITXC,IYOO,ITZC)).EQ.1
     $           .AND.(INC(ITXC,ITYC,IZOO).EQ.INC(ITXC,IYOO,ITZC)))
     $           THEN
	              GOTO 21
                 END IF
	        ELSE IF(ITYC.EQ.IYOO.AND.
     $		   ITXC.NE.IXOO.AND.ITZC.NE.IZOO)THEN
	           IF(IABS(INB(ITXC,ITYC,IZOO)-INB(IXOO,ITYC,ITZC)).EQ.1
     $	       .AND.(INC(ITXC,ITYC,IZOO).EQ.INC(IXOO,ITYC,ITZC)))
     $           THEN
	              GOTO 21
	           END IF
	        ELSE IF(ITZC.EQ.IZOO.AND.
     $		   ITXC.NE.IXOO.AND.ITYC.NE.IYOO)THEN
	           IF(IABS(INB(ITXC,IYOO,ITZC)-INB(IXOO,ITYC,ITZC)).EQ.1
     $           .AND.(INC(ITXC,IYOO,ITZC).EQ.INC(IXOO,ITYC,ITZC)))
     $           THEN
	              GOTO 21
                 END IF
	        END IF
	        XC(IC)=XPP(1)
	        YC(IC)=YPP(1)
	        ZC(IC)=ZPP(1)
	        DO KK=1,NBEAD-1
	           X(I,KK)=XPP(KK+1)
	           Y(I,KK)=YPP(KK+1)
	           Z(I,KK)=ZPP(KK+1)
	           INC(X(I,KK),Y(I,KK),Z(I,KK))=I
	           INB(X(I,KK),Y(I,KK),Z(I,KK))=KK
     	        END DO
	        X(I,NBEAD)=ITXC
	        Y(I,NBEAD)=ITYC
	        Z(I,NBEAD)=ITZC
              INC(X(I,NBEAD),Y(I,NBEAD),Z(I,NBEAD))=I
	        INB(X(I,NBEAD),Y(I,NBEAD),Z(I,NBEAD))=NBEAD
	        INC(XC(IC),YC(IC),ZC(IC))=0
	        INB(XC(IC),YC(IC),ZC(IC))=0	         
	     END IF
	  END IF
	END IF  
21    CONTINUE
      RETURN
	END
	
	  
	  SUBROUTINE ENERGY1(I1COUNT,I2COUNT,I3COUNT,I4COUNT,I5COUNT,I,J)
***************************************************************************
*                           THIS SUBROUTINE CALCULATE ENERGY              *
***************************************************************************
      IMPLICIT NONE
      INTEGER*4 NCHAIN,NBEAD,NBA,NBB   
      INTEGER*4 LX,LY,LZ
      INTEGER*4 X(25000,20),Y(25000,20),Z(25000,20)
      INTEGER*4 INC(110,110,50),INB(110,110,50),I,J
      INTEGER*4 IX,IY,IZ
	INTEGER*4 PX,PY,PZ
	INTEGER*4 I1COUNT,I2COUNT,I3COUNT,I4COUNT,I5COUNT
	INTEGER  IDUM
C
C
      COMMON/POSITION/X,Y,Z
      COMMON/OCCUPY/INC,INB
      COMMON/BEAD/NCHAIN,NBEAD
      COMMON/PER_BEAD/NBA,NBB
      COMMON/IDUM/IDUM
      COMMON/LATTICE/LX,LY,LZ 
C
	I1COUNT=0
	I2COUNT=0
	I3COUNT=0
	I4COUNT=0
	I5COUNT=0	
	IF(J.LE.NBA.AND.J.NE.0)THEN
	      IF(Z(I,J).EQ.1)THEN	           		
	             I2COUNT=I2COUNT+1
	      ELSE IF(Z(I,J).EQ.LZ)THEN
		         I4COUNT=I4COUNT+1	
	      END IF	         
	      DO IX=0,2
		     DO IY=0,2
			    DO IZ=0,2			       
				   IF(IABS(IX-1).EQ.IABS(IY-1).AND.IABS(IY-1)
     $			     .EQ.IABS(IZ-1))THEN
				      GOTO 23
				   END IF
                     PX=X(I,J)+IX-1
	               PY=Y(I,J)+IY-1
	               PZ=Z(I,J)+IZ-1	  	              
				   IF(PX.GT.LX)THEN
					     PX=PX-LX
	               ELSE IF(PX.LT.1)THEN
	                     PX=PX+LX
	               END IF
	               IF(PY.GT.LY)THEN
	                     PY=PY-LY
	               ELSE IF(PY.LT.1)THEN
	                     PY=PY+LY
	               END IF
				   IF(PZ.GT.LZ.OR.PZ.LT.1) THEN
	                     GOTO 23
	               ELSE IF(INB(PX,PY,PZ).GT.NBA
     $				     .AND.INB(PX,PY,PZ).LE.NBEAD) THEN
                           I1COUNT=I1COUNT+1
				   END IF
23	               CONTINUE
                  END DO
			 END DO
		  END DO
	   
	   ELSE IF(J.GT.NBA.AND.J.LE.NBEAD)THEN
	      IF(Z(I,J).EQ.1)THEN	           		
	             I3COUNT=I3COUNT+1
	      ELSE IF(Z(I,J).EQ.LZ)THEN
		         I5COUNT=I5COUNT+1	
	      END IF
	      DO IX=0,2
		     DO IY=0,2
	            DO IZ=0,2
	               IF(IABS(IX-1).EQ.IABS(IY-1).AND.IABS(IY-1)
     $			     .EQ.IABS(IZ-1))THEN
	                  GOTO 24
                     END IF
                     PX=X(I,J)+IX-1
	               PY=Y(I,J)+IY-1
	               PZ=Z(I,J)+IZ-1
	               IF(PX.GT.LX)THEN
	                  PX=PX-LX
	               ELSE IF(PX.LT.1)THEN
	                  PX=PX+LX
	               END IF
	               IF(PY.GT.LY)THEN
	                  PY=PY-LY
	               ELSE IF(PY.LT.1)THEN
	                  PY=PY+LY
	               END IF
	               IF(PZ.GT.LZ.OR.PZ.LT.1)THEN
	                  GOTO 24
	               ELSE IF(INB(PX,PY,PZ).LE.NBA.AND.
     $			         INB(PX,PY,PZ).NE.0)THEN
                           I1COUNT=I1COUNT+1
			 	   END IF				    				    
24                   CONTINUE
                  END DO
			 END DO
		  END DO
	   END IF	
	RETURN
	END 

	                  
	   SUBROUTINE ENERGY2(I1COUNT,I2COUNT,I4COUNT,I,J)
***************************************************************************
*                           THIS SUBROUTINE CALCULATE ENERGY              *
***************************************************************************
      IMPLICIT NONE
      INTEGER*4 NCHAIN,NBEAD,NBA,NBB   
      INTEGER*4 LX,LY,LZ
      INTEGER*4 X(25000,20),Y(25000,20),Z(25000,20)
      INTEGER*4 INC(110,110,50),INB(110,110,50),I,J
      INTEGER*4 IX,IY,IZ
	INTEGER*4 PX,PY,PZ,PPX
	INTEGER*4 I1COUNT,I2COUNT,I4COUNT
	INTEGER  IDUM
C
C
      COMMON/POSITION/X,Y,Z
      COMMON/OCCUPY/INC,INB
      COMMON/BEAD/NCHAIN,NBEAD
      COMMON/PER_BEAD/NBA,NBB
      COMMON/IDUM/IDUM
      COMMON/LATTICE/LX,LY,LZ 
C
	I1COUNT=0
	I2COUNT=0
C	I3COUNT=0
	I4COUNT=0
C	I5COUNT=0
	IF(Z(I,J).EQ.1)THEN
	   I2COUNT=I2COUNT+1
	ELSE IF(Z(I,J).EQ.LZ)THEN
	   I4COUNT=I4COUNT+1
	END IF
	DO IX=0,2
	   DO IY=0,2
	      DO IZ=0,2			       
	         IF(IABS(IX-1).EQ.IABS(IY-1).AND.IABS(IY-1)
     $ 		    .EQ.IABS(IZ-1))THEN
			    GOTO 25
			 END IF
               PX=X(I,J)+IX-1
	         PY=Y(I,J)+IY-1
	         PZ=Z(I,J)+IZ-1
		    IF(PX.GT.LX)THEN
			   PX=PX-LX
              ELSE IF(PX.LT.1)THEN
                 PX=PX+LX
              END IF
              IF(PY.GT.LY)THEN
                 PY=PY-LY
              ELSE IF(PY.LT.1)THEN
                 PY=PY+LY
              END IF
	        IF(PZ.GT.LZ.OR.PZ.LT.1)THEN
	           GOTO 25
	        ELSE IF(INB(PX,PY,PZ).GT.NBA
     $	           .AND.INB(PX,PY,PZ).LE.NBEAD)THEN
                 I1COUNT=I1COUNT+1
			END IF			
25            CONTINUE
            END DO
	   END DO
	END DO
      RETURN
	END 

	    SUBROUTINE ENERGY3(I1COUNT,I2COUNT,I3COUNT,I4COUNT,I5COUNT,I)
***************************************************************************
*                           THIS SUBROUTINE CALCULATE ENERGY              *
***************************************************************************
      IMPLICIT NONE
      INTEGER*4 NCHAIN,NBEAD,NBA,NBB   
      INTEGER*4 LX,LY,LZ
      INTEGER*4 X(25000,20),Y(25000,20),Z(25000,20)
      INTEGER*4 INC(110,110,50),INB(110,110,50),I,J
      INTEGER*4 IX,IY,IZ
	INTEGER*4 PX,PY,PZ,PPX
	INTEGER*4 I1COUNT,I2COUNT,I3COUNT,I4COUNT,I5COUNT
	INTEGER  IDUM
C
C
      COMMON/POSITION/X,Y,Z
      COMMON/OCCUPY/INC,INB
      COMMON/BEAD/NCHAIN,NBEAD
      COMMON/PER_BEAD/NBA,NBB
      COMMON/IDUM/IDUM
      COMMON/LATTICE/LX,LY,LZ 
C
	I1COUNT=0
	I2COUNT=0
	I3COUNT=0
	I4COUNT=0
	I5COUNT=0
	DO J=1,NBEAD
	   IF(J.LE.NBA.AND.J.NE.0)THEN
	      IF(Z(I,J).EQ.1)THEN
	         I2COUNT=I2COUNT+1
	      ELSE IF(Z(I,J).EQ.LZ)THEN
	         I4COUNT=I4COUNT+1
	      END IF
	      DO IX=0,2
		     DO IY=0,2
			    DO IZ=0,2			       
				   IF(IABS(IX-1).EQ.IABS(IY-1).AND.IABS(IY-1)
     $			     .EQ.IABS(IZ-1))THEN
				      GOTO 26
				   END IF
                     PX=X(I,J)+IX-1
	               PY=Y(I,J)+IY-1
	               PZ=Z(I,J)+IZ-1
	               IF(PX.GT.LX)THEN
	                  PX=PX-LX
	               ELSE IF(PX.LT.1)THEN
	                  PX=PX+LX
	               END IF
	               IF(PY.GT.LY)THEN
	                  PY=PY-LY
	               ELSE IF(PY.LT.1)THEN
	                  PY=PY+LY
	               END IF
	               IF(PZ.GT.LZ.OR.PZ.LT.1) THEN
	                  GOTO 26
	               ELSE IF(INB(PX,PY,PZ).GT.NBA.AND.
     $				   INC(PX,PY,PZ).NE.0)THEN
                         I1COUNT=I1COUNT+1
				   END IF
26                   CONTINUE
                  END DO
			 END DO
		  END DO
	   ELSE IF(J.GT.NBA)THEN
	      IF(Z(I,J).EQ.1)THEN
	         I3COUNT=I3COUNT+1
	      ELSE IF(Z(I,J).EQ.LZ)THEN
	         I5COUNT=I5COUNT+1          
	      END IF
	      DO IX=0,2
		     DO IY=0,2
	            DO IZ=0,2
	               IF(IABS(IX-1).EQ.IABS(IY-1).AND.IABS(IY-1)
     $			     .EQ.IABS(IZ-1))THEN
	                  GOTO 27
                     END IF
                     PX=X(I,J)+IX-1
	               PY=Y(I,J)+IY-1
	               PZ=Z(I,J)+IZ-1
	               IF(PX.GT.LX)THEN
	                  PX=PX-LX
	               ELSE IF(PX.LT.1)THEN
	                  PX=PX+LX
	               END IF
	               IF(PY.GT.LY)THEN
	                  PY=PY-LY
	               ELSE IF(PY.LT.1)THEN
	                  PY=PY+LY
	               END IF
	               IF(PZ.GT.LZ.OR.PZ.LT.1)THEN
	                  GOTO 27     
	               ELSE IF(INB(PX,PY,PZ).LE.NBA.AND.
     $			         INB(PX,PY,PZ).NE.0)THEN
                           I1COUNT=I1COUNT+1
			 	   END IF				  		    
27                   CONTINUE
                  END DO
			 END DO
		  END DO
	   END IF	
	END DO
	RETURN
      END
	      
		      SUBROUTINE ENERGY4(I1COUNT,I3COUNT,I5COUNT,I,J)
***************************************************************************
*                           THIS SUBROUTINE CALCULATE ENERGY              *
***************************************************************************
      IMPLICIT NONE
      INTEGER*4 NCHAIN,NBEAD,NBA,NBB   
      INTEGER*4 LX,LY,LZ
      INTEGER*4 X(25000,20),Y(25000,20),Z(25000,20)
      INTEGER*4 INC(110,110,50),INB(110,110,50),I,J
      INTEGER*4 IX,IY,IZ
	INTEGER*4 PX,PY,PZ,PPX
	INTEGER*4 I1COUNT,I3COUNT,I5COUNT
	INTEGER  IDUM
C
C
      COMMON/POSITION/X,Y,Z
      COMMON/OCCUPY/INC,INB
      COMMON/BEAD/NCHAIN,NBEAD
      COMMON/PER_BEAD/NBA,NBB
      COMMON/IDUM/IDUM
      COMMON/LATTICE/LX,LY,LZ 
C
	I1COUNT=0
C	I2COUNT=0
	I3COUNT=0
C	I4COUNT=0
	I5COUNT=0
	IF(Z(I,J).EQ.1)THEN
	   I3COUNT=I3COUNT+1
	ELSE IF(Z(I,J).EQ.LZ)THEN
	   I5COUNT=I5COUNT+1
	END IF
	DO IX=0,2
	   DO IY=0,2
	      DO IZ=0,2			       
	         IF(IABS(IX-1).EQ.IABS(IY-1).AND.IABS(IY-1)
     $ 		    .EQ.IABS(IZ-1))THEN
			    GOTO 28
			 END IF
               PX=X(I,J)+IX-1
	         PY=Y(I,J)+IY-1
	         PZ=Z(I,J)+IZ-1
	         IF(PX.GT.LX)THEN
			    PX=PX-LX
	         ELSE IF(PX.LT.1)THEN
	            PX=PX+LX
	         END IF
	         IF(PY.GT.LY)THEN
	            PY=PY-LY
	         ELSE IF(PY.LT.1)THEN
	            PY=PY+LY
	         END IF
	         IF(PZ.GT.LZ.OR.PZ.LT.1)THEN
	            GOTO 28
	         ELSE IF(INB(PX,PY,PZ).LE.NBA
     $			   .AND.INB(PX,PY,PZ).NE.0) THEN
                     I1COUNT=I1COUNT+1			
			 END IF
28             CONTINUE
            END DO
	   END DO
	END DO
      RETURN
	END 



	 
			 
	                     SUBROUTINE PERIOD(I,J)
***************************************************************************
*	     THIS SUBROUTINE IMPOSES PERIODIC BOUNDARY CONDITIONS	        *
***************************************************************************
	IMPLICIT NONE
	INTEGER*4 NCHAIN,NBEAD,LX,LY,LZ
      INTEGER*4 X(25000,20),Y(25000,20),Z(25000,20)
	INTEGER*4 I,J
	
      COMMON/POSITION/X,Y,Z
      COMMON/LATTICE/LX,LY,LZ      
      COMMON/BEAD/NCHAIN,NBEAD
      	
      IF(X(I,J).GT.LX)THEN 
	   X(I,J)=X(I,J)-LX
	ELSE IF(X(I,J).LT.1)THEN
	   X(I,J)=X(I,J)+LX
	END IF
	IF(Y(I,J).GT.LY)THEN
	   Y(I,J)=Y(I,J)-LY
	ELSE IF(Y(I,J).LT.1)THEN
	   Y(I,J)=Y(I,J)+LY
	END IF
	RETURN
	END                     
	
C      
	                  FUNCTION ran2(IDUM)
**************************************************************************
*		        CALCULATE RANDOM DTAE                                  *
**************************************************************************     
      INTEGER idum,IM1,IM2,IMM1,IA1,IA2,IQ1,IQ2,IR1,IR2,NTAB,NDIV
      REAL ran2,AM,EPS,RNMX
      PARAMETER (IM1=2147483563,IM2=2147483399,AM=1./IM1,IMM1=IM1-1,
     *IA1=40014,IA2=40692,IQ1=53668,IQ2=52774,IR1=12211,IR2=3791,
     *NTAB=32,NDIV=1+IMM1/NTAB,EPS=1.2e-7,RNMX=1.-EPS)
	INTEGER idum2,j,k,iv(NTAB),iy
      SAVE iv,iy,idum2
      DATA idum2/123456789/, iv/NTAB*0/, iy/0/
      if (idum.le.0) then
        idum=max(-idum,1)
        idum2=idum
        do 11 j=NTAB+8,1,-1
          k=idum/IQ1
          idum=IA1*(idum-k*IQ1)-k*IR1
          if (idum.lt.0) idum=idum+IM1
          if (j.le.NTAB) iv(j)=idum
11      continue
        iy=iv(1)
      endif
      k=idum/IQ1
      idum=IA1*(idum-k*IQ1)-k*IR1
      if (idum.lt.0) idum=idum+IM1
      k=idum2/IQ2
      idum2=IA2*(idum2-k*IQ2)-k*IR2
      if (idum2.lt.0) idum2=idum2+IM2
      j=1+iy/NDIV
      iy=iv(j)-idum2
      iv(j)=idum
      if(iy.lt.1)iy=iy+IMM1
      ran2=min(AM*iy,RNMX)
      return
      END


