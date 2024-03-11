#ifndef TGRAPHICS_H
#define TGRAPHICS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

#define Max_Width 512
#define Max_Height 512
#define G_PI 3.14159265359



namespace  graphics{

    typedef enum {UP, DOWN, LEFT, RIGHT}Direction;

    // Reset 
    const char * const Color_Off = "\033[0m";       //Text Reset

    // Regular Colors
    const char * const Black = "\033[0;30m";        //Black
    const char * const Red = "\033[0;31m";          //Red
    const char * const Green = "\033[0;32m";        //Green
    const char * const Yellow = "\033[0;33m";       //Yellow
    const char * const Blue = "\033[0;34m";         //Blue
    const char * const Purple = "\033[0;35m";       //Purple
    const char * const Cyan = "\033[0;36m";         //Cyan
    const char * const White = "\033[0;37m";        //White

    // Bold
    const char * const BBlack = "\033[1;30m";       //Black
    const char * const BRed = "\033[1;31m";         //Red
    const char * const BGreen = "\033[1;32m";       //Green
    const char * const BYellow = "\033[1;33m";      //Yellow
    const char * const BBlue = "\033[1;34m";        //Blue
    const char * const BPurple = "\033[1;35m";      //Purple
    const char * const BCyan = "\033[1;36m";        //Cyan
    const char * const BWhite = "\033[1;37m";       //White
                                                        //
    // Dark
    const char * const DBlack = "\033[2;30m";       //Black
    const char * const DRed = "\033[2;31m";         //Red
    const char * const DGreen = "\033[2;32m";       //Green
    const char * const DYellow = "\033[2;33m";      //Yellow
    const char * const DBlue = "\033[2;34m";        //Blue
    const char * const DPurple = "\033[2;35m";      //Purple
    const char * const DCyan = "\033[2;36m";        //Cyan
    const char * const DWhite = "\033[2;37m";       //White

    // Underline
    const char * const UBlack = "\033[4;30m";       //Black
    const char * const URed = "\033[4;31m";         //Red
    const char * const UGreen = "\033[4;32m";       //Green
    const char * const UYellow = "\033[4;33m";      //Yellow
    const char * const UBlue = "\033[4;34m";        //Blue
    const char * const UPurple = "\033[4;35m";      //Purple
    const char * const UCyan = "\033[4;36m";        //Cyan
    const char * const UWhite = "\033[4;37m";       //White

    // High Intensity
    const char * const IBlack = "\033[0;90m";       //Black
    const char * const IRed = "\033[0;91m";         //Red
    const char * const IGreen = "\033[0;92m";       //Green
    const char * const IYellow = "\033[0;93m";      //Yellow
    const char * const IBlue = "\033[0;94m";        //Blue
    const char * const IPurple = "\033[0;95m";      //Purple
    const char * const ICyan = "\033[0;96m";        //Cyan
    const char * const IWhite = "\033[0;97m";       //White

    // Bold High Intensity
    const char * const BIBlack = "\033[1;90m";      //Black
    const char * const BIRed = "\033[1;91m";        //Red
    const char * const BIGreen = "\033[1;92m";      //Green
    const char * const BIYellow = "\033[1;93m";     //Yellow
    const char * const BIBlue = "\033[1;94m";       //Blue
    const char * const BIPurple = "\033[1;95m";     //Purple
    const char * const BICyan = "\033[1;96m";       //Cyan
    const char * const BIWhite = "\033[1;97m";      //White

    // Background
    const char * const On_Black = "\033[40m";       //Black
    const char * const On_Red = "\033[41m";         //Red
    const char * const On_Green = "\033[42m";       //Green
    const char * const On_Yellow = "\033[43m";      //Yellow
    const char * const On_Blue = "\033[44m";        //Blue
    const char * const On_Purple = "\033[45m";      //Purple
    const char * const On_Cyan = "\033[46m";        //Cyan
    const char * const On_White = "\033[47m";       //White
    
    // on red background
    const char * const Black_On_Red = "\033[7;31;40m";       //Black
    const char * const Green_On_Red = "\033[7;31;42m";       //Green
    const char * const Yellow_On_Red = "\033[7;31;43m";       //Yellow
    const char * const Blue_On_Red = "\033[7;31;44m";       //Blue
    const char * const Purple_On_Red = "\033[7;31;45m";       //Purple
    const char * const Cyan_On_Red = "\033[7;31;46m";       //Cyan
    const char * const White_On_Red = "\033[7;31;47m";       //White

    // On Green Background const 
    const char * const Black_On_Green = "\033[7;32;40m";       //Black
    const char * const Red_On_Green = "\033[7;32;41m";       //Red
    const char * const Yellow_On_Green = "\033[7;32;43m";       //Yellow
    const char * const Blue_On_Green = "\033[7;32;44m";       //Blue
    const char * const Purple_On_Green = "\033[7;32;45m";       //Purple
    const char * const Cyan_On_Green = "\033[7;32;46m";       //Cyan
    const char * const White_On_Green = "\033[7;32;47m";       //White

    // On Yellow Backgroun const 
    const char * const Black_On_Yellow = "\033[7;33;40m";       //Black
    const char * const Red_On_Yellow = "\033[7;33;41m";       //Red
    const char * const Green_On_Yellow = "\033[7;33;42m";       //Green
    const char * const Blue_On_Yellow = "\033[7;33;44m";       //Blue
    const char * const Purple_On_Yellow = "\033[7;33;45m";       //Purple
    const char * const Cyan_On_Yellow = "\033[7;33;46m";       //Cyan
    const char * const White_On_Yellow = "\033[7;33;47m";       //White

    // On Blue Background const 
    const char * const Black_On_Blue = "\033[7;34;40m";       //Black
    const char * const Red_On_Blue = "\033[7;34;41m";       //Red
    const char * const Green_On_Blue = "\033[7;34;42m";       //Green
    const char * const Yellow_On_Blue = "\033[7;34;43m";       //Yellow
    const char * const Purple_On_Blue = "\033[7;34;45m";       //Purple
    const char * const Cyan_On_Blue = "\033[7;34;46m";       //Cyan
    const char * const White_On_Blue = "\033[7;34;47m";       //White

    // On Purple Backgroun const 
    const char * const Black_On_Purple = "\033[7;35;40m";       //Black
    const char * const Red_On_Purple = "\033[7;35;41m";       //Red
    const char * const Green_On_Purple = "\033[7;35;42m";       //Green
    const char * const Yellow_On_Purple = "\033[7;35;43m";       //Yellow
    const char * const Blue_On_Purple = "\033[7;35;44m";       //Blue
    const char * const Cyan_On_Purple = "\033[7;35;46m";       //Cyan
    const char * const White_On_Purple = "\033[7;35;47m";       //White

    // On Cyan Background const 
    const char * const Black_On_Cyan = "\033[7;36;40m";       //Black
    const char * const Red_On_Cyan = "\033[7;36;41m";       //Red
    const char * const Green_On_Cyan = "\033[7;36;42m";       //Green
    const char * const Yellow_On_Cyan = "\033[7;36;43m";       //Yellow
    const char * const Blue_On_Cyan = "\033[7;36;44m";       //Blue
    const char * const Purple_On_Cyan = "\033[7;36;45m";       //Purple
    const char * const White_On_Cyan = "\033[7;36;47m";       //White

    // On White Background const 
    const char * const Black_On_White = "\033[7;37;40m";       //Black
    const char * const Red_On_White = "\033[7;37;41m";       //Red
    const char * const Green_On_White = "\033[7;37;42m";       //Green
    const char * const Yellow_On_White = "\033[7;37;43m";       //Yellow
    const char * const Blue_On_White = "\033[7;37;44m";       //Blue
    const char * const Purple_On_White = "\033[7;37;45m";       //Purple
    const char * const Cyan_On_White = "\033[7;37;46m";       //Cyan

    // High Intensity back const rounds
    const char * const On_IBlack = "\033[0;100m";   //Black
    const char * const On_IRed = "\033[0;101m";     //Red
    const char * const On_IGreen = "\033[0;102m";   //Green
    const char * const On_IYellow = "\033[0;103m";  //Yellow
    const char * const On_IBlue = "\033[0;104m";    //Blue
    const char * const On_IPurple = "\033[0;105m";  //Purple
    const char * const On_ICyan = "\033[0;106m";    //Cyan
    const char * const On_IWhite = "\033[0;107m";   //White


    
    const char * const SolidPixel = "█";
    const char * const DarkPixel = "▓";
    const char * const MidPixel = "▒";
    const char * const LightPixel = "░";
    const char * const SmolPixel = "■";

    inline int GetLen(const char *c){
        int index = 0;
        while(*c != '\0'){
            c++;
            index = index + 1;
        }
        // to hold the \0
        index = index + 1;
        return index;
    }

    inline void EasyChar(char c, char *word){
        word[0] = c;
        word[1] = '\0';
    }

    inline void EasyColor(const char* Color, char *out){
        int i = 0;
        while(Color[i] != '\0'){
            out[i] = Color[i];
            i += 1;
        }
        out[i] = '\0';
        return;
    }

    inline void EasyBody(const char* Body, char *out){
        int i = 0;
        while(Body[i] != '\0'){
            out[i] = Body[i];
            i += 1;
        }
        out[i] = '\0';
        return;
    }

    typedef struct Pixel{
        //Point Pos;
        char *Color;
        char *Body;
        Pixel(const char *Color = nullptr, const char *Body = nullptr){
            this->Color = (char *)malloc(16);
            if(Color == nullptr){
                EasyColor(Color_Off,this->Color);
            } else {
                EasyColor(Color,this->Color);
            }

            this->Body = (char *)malloc(5);

            if(Body == nullptr){
                EasyBody(SolidPixel,this->Body);
            } else {
                EasyBody(Body,this->Body);
            }
        } 


    } Pixel;

    template <typename T>
    struct Point{
        T X;
        T Y;

        Point(T X = -1, T Y = -1) : X(X), Y(Y){

        }

        /*
        Point& operator=(const Point& P){
            this->X = P.X;
            this->Y = P.Y;
            return *this;
        }
        */

        Point<T>& operator+(const Point<T>& P){
            this->X += P.X;
            this->Y += P.Y;
            return *this;
        }
        Point<T>& operator-(const Point<T>& P){
            this->X -= P.X;
            this->Y -= P.Y;
            return *this;
        }


        Point<T>& operator*(const Point<T>& P){
            this->X *= P.X;
            this->Y *= P.Y;
            return *this;
        }
        Point<T>& operator/(const Point<T>& P){
            this->X /= P.X;
            this->Y /= P.Y;
            return *this;
        }
    };

    template <typename T>
    struct Line{
        int Count;
        Point<T> *Points;

        Line(int Count = -1, Point<T> *Points = NULL) : Count(Count), Points(Points){

        }

        Line (Line const& ) = default;

    };

    // Has to be ints
    template <typename T>
    inline struct Line<T> GetLine(T x1,T y1, T x2, T y2){
        T dx = abs(x2 - x1);
        T dy = abs(y2 - y1);
        T sx = x1 < x2 ? 1 : -1;
        T sy = y1 < y2 ? 1 : -1;
        T err = dx - dy;
        int i = 0;
        struct Line<T> line(0,(Point<T>*) malloc(sizeof(Point<T>)*(dx+dy+1)));

        while ((int)x1 != (int)x2 || (int)y1 != (int)y2) {
            line.Points[i].X = x1;
            line.Points[i].Y = y1;
            T e2 = err * 2;
            if (e2 > -dy) {
                err -= dy;
                x1 += sx;
            }
            if (e2 < dx) {
                err += dx;
                y1 += sy;
            }
            i++;
            line.Points[i].X = x1;
            line.Points[i].Y = y1;
            if(i == dx+dy){
                break;
            }
        }
        line.Count = i;
        return line;

    }


    // Added for 3D Maths
    template <typename T>
        struct Point3D{
            T X;
            T Y;
            T Z;
            Point3D(T X = 0, T Y = 0, T Z = 0) : X(X), Y(Y), Z(Z){};
                
            Point3D<T>& operator+(const Point3D<T>& P){
                this->X += P.X;
                this->Y += P.Y;
                this->Z += P.Z;
                return *this;
            }
            Point3D<T>& operator-(const Point3D<T>& P){
                this->X -= P.X;
                this->Y -= P.Y;
                this->Z -= P.Z;
                return *this;
            }
            Point3D<T>& operator*(const Point3D<T>& P){
                this->X *= P.X;
                this->Y *= P.Y;
                this->Z *= P.Z;
                return *this;
            }
            Point3D<T>& operator/(const Point3D<T>& P){
                this->X /= P.X;
                this->Y /= P.Y;
                this->Z /= P.Z;
                return *this;
            }
        };

    template <typename T>
        struct Line3D{
            int Count;
            Point3D<T> *Points;

            Line3D(int Count = -1, Point3D<T> *Points = NULL) : Count(Count), Points(Points){

            }

        };


    template <typename T>
        inline Line3D<T> TranslateLine3D(Line3D<T> &L, Point3D<T> &P){
            Line3D<T> out;
            out.Count = L.Count;
            out.Points = (Point3D<T>*)malloc( sizeof(Point3D<T>) * L.Count );
            for(int i = 0; i < L.Count; i++){
                out.Points[i] = L.Points[i] + P;
            }
            return out;
        }

    template <typename T>
        struct Matrix2x3{
            Point3D<T> A;
            Point3D<T> B;

            Matrix2x3(T X = 0, T Y = 0){
                A.X = X;
                B.Y = Y;
            }

            void QuickSet(T X, T Y){
                this->A.X = X;
                this->B.Y = Y;
            }

        };


    template <typename T>
        struct Matrix3x3{
            Point3D<T> A;
            Point3D<T> B;
            Point3D<T> C;

            Matrix3x3(T X = 0, T Y = 0, T Z = 0){
                A.X = X;
                B.Y = Y;
                C.Z = Z;
            }

            void QuickSet(T X, T Y, T Z){
                this->A.X = X;
                this->B.Y = Y;
                this->C.Z = Z;
            }

        };

    template <typename T>
        inline Point3D<T> Point3DMultMat2x3(Point3D<T> &P, Matrix2x3<T> &M){
            Point3D<T> out;
            out.X = P.X * M.A.X + P.Y * M.A.Y + P.Z * M.A.Z;
            out.Y = P.X * M.B.X + P.Y * M.B.Y + P.Z * M.B.Z;
            out.Z = 0;

            return out;
        }



    template <typename T>
        inline Line3D<T> Line3DMultMat2x3(Line3D<T> &L, Matrix2x3<T> &M){
            Line3D<T> out;
            out.Points = (Point3D<T>*)malloc(sizeof(Point3D<T>) * L.Count);
            out.Count = L.Count;
            for(int i = 0; i < L.Count; i++){
                out.Points[i].X = L.Points[i].X * M.A.X + L.Points[i].Y * M.A.Y + L.Points[i].Z * M.A.Z;
                out.Points[i].Y = L.Points[i].X * M.B.X + L.Points[i].Y * M.B.Y + L.Points[i].Z * M.B.Z;
                out.Points[i].Z = 0;
            }

            return out;
        }


    template <typename T>
        inline Point3D<T> Point3DMultMat3x3(Point3D<T> &P, Matrix3x3<T> &M){
            Point3D<T> out;
            out.X = P.X * M.A.X + P.Y * M.A.Y + P.Z * M.A.Z;
            out.Y = P.X * M.B.X + P.Y * M.B.Y + P.Z * M.B.Z;
            out.Z = P.X * M.C.X + P.Y * M.C.Y + P.Z * M.C.Z;

            return out;
        }

    template <typename T, typename R>
        inline Line3D<T> RotateX(Line3D<T> &L, R Angle){
            Angle = Angle *  G_PI /180;
            Matrix3x3<T> M;
            Line3D<T> out;
            out.Points = (Point3D<T>*)malloc(sizeof(Point3D<T>) * L.Count);
            out.Count = L.Count;

            M.A.X = 1;
            M.A.Y = 0;
            M.A.Z = 0;

            M.B.X = 0;
            M.B.Y = cos(Angle);
            M.B.Z = -sin(Angle);

            M.C.X = 0;
            M.C.Y = sin(Angle);
            M.C.Z = cos(Angle);

            for(int i = 0; i < L.Count; i++){
                out.Points[i].X = L.Points[i].X * M.A.X + L.Points[i].Y * M.A.Y + L.Points[i].Z * M.A.Z;
                out.Points[i].Y = L.Points[i].X * M.B.X + L.Points[i].Y * M.B.Y + L.Points[i].Z * M.B.Z;
                out.Points[i].Z = L.Points[i].X * M.C.X + L.Points[i].Y * M.C.Y + L.Points[i].Z * M.C.Z;
            }

            return out;
        }


    template <typename T, typename R>
        inline Line3D<T> RotateY(Line3D<T> &L, R Angle){
            Angle = Angle *  G_PI /180;
            Matrix3x3<T> M;
            Line3D<T> out;
            out.Points = (Point3D<T>*)malloc(sizeof(Point3D<T>) * L.Count);
            out.Count = L.Count;

            M.A.X = cos(Angle);
            M.A.Y = 0;
            M.A.Z = -sin(Angle);

            M.B.X = 0;
            M.B.Y = 1;
            M.B.Z = 0;

            M.C.X = sin(Angle);
            M.C.Y = 0;
            M.C.Z = cos(Angle);

            for(int i = 0; i < L.Count; i++){
                out.Points[i].X = L.Points[i].X * M.A.X + L.Points[i].Y * M.A.Y + L.Points[i].Z * M.A.Z;
                out.Points[i].Y = L.Points[i].X * M.B.X + L.Points[i].Y * M.B.Y + L.Points[i].Z * M.B.Z;
                out.Points[i].Z = L.Points[i].X * M.C.X + L.Points[i].Y * M.C.Y + L.Points[i].Z * M.C.Z;
            }

            return out;
        }


    template <typename T, typename R>
        inline Line3D<T> RotateZ(Line3D<T> &L, R Angle){
            Angle = Angle *  G_PI /180;
            Matrix3x3<T> M;
            Line3D<T> out;
            out.Points = (Point3D<T>*)malloc(sizeof(Point3D<T>) * L.Count);
            out.Count = L.Count;
            M.A.X = cos(Angle);
            M.A.Y = -sin(Angle);
            M.A.Z = 0;

            M.B.X = sin(Angle);
            M.B.Y = cos(Angle);
            M.B.Z = 0;

            M.C.X = 0;
            M.C.Y = 0;
            M.C.Z = 1;

            for(int i = 0; i < L.Count; i++){
                out.Points[i].X = L.Points[i].X * M.A.X + L.Points[i].Y * M.A.Y + L.Points[i].Z * M.A.Z;
                out.Points[i].Y = L.Points[i].X * M.B.X + L.Points[i].Y * M.B.Y + L.Points[i].Z * M.B.Z;
                out.Points[i].Z = L.Points[i].X * M.C.X + L.Points[i].Y * M.C.Y + L.Points[i].Z * M.C.Z;
            }

            return out;
        }



    template <typename T>
            inline Line3D<T> Line3DMultMat3x3(Line3D<T> &L, Matrix3x3<T> &M){
                Line3D<T> out;
                out.Points = (Point3D<T>*)malloc(sizeof(Point3D<T>) * L.Count);
                out.Count = L.Count;
                for(int i = 0; i < L.Count; i++){
                    out.Points[i].X = L.Points[i].X * M.A.X + L.Points[i].Y * M.A.Y + L.Points[i].Z * M.A.Z;
                    out.Points[i].Y = L.Points[i].X * M.B.X + L.Points[i].Y * M.B.Y + L.Points[i].Z * M.B.Z;
                    out.Points[i].Z = L.Points[i].X * M.C.X + L.Points[i].Y * M.C.Y + L.Points[i].Z * M.C.Z;
                }

                return out;
            }





        template <typename T>
            inline Line3D<T> GetLine3D(T x1,T y1,T z1, T x2, T y2, T z2){
                T dx = abs(x2 - x1);
                T dy = abs(y2 - y1);
                T dz = abs(z2 - z1);
                T sx = x1 < x2 ? 1 : -1;
                T sy = y1 < y2 ? 1 : -1;
                T sz = z1 < z2 ? 1 : -1;
                T err1 = dx - dy;
                T err2 = dx - dz;
                T i = 0;
                Line3D<T> line;
                line.Points = (Point3D<T>*)malloc(sizeof(Point3D<T>) * (dx + dy + dz + 1));

                if (line.Points == NULL) {
                    // Handle memory allocation failure
                    line.Count = 0;
                    return line;
                }

                int x = x1, y = y1, z = z1;
                while (x != x2 || y != y2 || z != z2) {
                    line.Points[i].X = x;
                    line.Points[i].Y = y;
                    line.Points[i].Z = z;
                    T e2 = err1 * 2;
                    T e3 = err2 * 2;

                    if (e2 > -dy) {
                        err1 -= dy;
                        x += sx;
                    }
                    if (e2 < dx) {
                        err1 += dx;
                        y += sy;
                    }
                    if (e3 < dx) {
                        err2 += dx;
                        z += sz;
                    }
                    i++;
                }
                line.Points[i].X = x2;
                line.Points[i].Y = y2;
                line.Points[i].Z = z2;
                line.Count = i + 1; // Number of points in the line
                return line;

            }

        template <typename T>
            inline bool Box3DCheck(Point3D<T> A, Point3D<T> &TL, Point3D<T> &BR){
                // we assume the point is not inside the box by defualt
                bool isPointInBox = false;
                float X,Y,Z;
                // Rgiht by Left
                X = (float)((2*A.X) - TL.X - BR.X)/ BR.X-TL.X;
                // Bottom to top
                Y = (float)((2*A.Y) - TL.Y - BR.Y)/ BR.Y-TL.Y;
                // Back to front
                Z = (float)((2*A.Z) - TL.Z - BR.Z)/ BR.Z-TL.Z;

                if(X >= 1 && X <= -1){
                    if(Y >= 1 && Y <= -1){
                        if(Z >= 1 && Z <= -1){
                            isPointInBox = true;
                        }
                    }
                }

                return isPointInBox;
            }

        template <typename T>
            inline void LazyBox(Point3D<T> P, T W, T H,T D, Point3D<T> *TLout, Point3D<T> *BRout){
                TLout->X = -W+P.X;
                TLout->Y = H+P.Y;
                // Diff Width and Height
                TLout->Z = -D+P.Z;

                BRout->X = W+P.X;
                BRout->Y = -H+P.Y;
                // Diff Width and Height
                BRout->Z = D+P.Z;

            }



        template <typename T>
        inline Line<T> MakeCircle(T X, T Y, T R, bool GCircle = false){
            Line<T> circle;
            int PMax = (R*2)*3;
            circle.Points = (Point<T> *)malloc(sizeof(Point<T>)*(PMax+1));
            int Pcount = 0;
            float Cut = 360.0f/(PMax);
            T a = 0;
            T b = 0;
            float tmp;
            // will be a define

            //circle is drawn arounds 0,0 and then the X and Y is added as an offset to the final points
            for(int i = 1; i <= PMax; i++){
                tmp = (float) (Cut *i) * G_PI /180;
                a = R*cosf(tmp);
                if(GCircle){
                    b = (R*0.8)*sinf(tmp);
                } else {
                    b = R*sinf(tmp);
                }

                circle.Points[Pcount].X = a+X;
                circle.Points[Pcount].Y = b+Y;

                Pcount = Pcount + 1;

                if(Pcount == PMax){ 
                    circle.Count = Pcount;
                    break;
                }

            }

            circle.Count = Pcount;

            return circle;
        }


        typedef struct Input{
          char KeyList[128];
          char SmartInputBuffer;
          int OldSystem_IOState;
          struct termios oldSettings;
          struct termios newSettings;

          inline void Init(){
              this->OldSystem_IOState = fcntl(STDIN_FILENO, F_GETFL);
              tcgetattr(STDIN_FILENO, &this->oldSettings); // Save current terminal settings
              this->newSettings = this->oldSettings;
              newSettings.c_lflag &= ~(ICANON | ECHO); // Turn off canonical mode and echo
              tcsetattr(STDIN_FILENO, TCSANOW, &this->newSettings); // Apply new terminal setting
              //fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL) | O_NONBLOCK); // Set STDIN to non blocking

               }

          inline void ThreadSmartInput(){
             char Key = getchar();
            if (Key == 27) { // Check if it's an escape sequence
                if (getchar() == '[') { // Verify the next character
                    switch (getchar()) { // Get the third character to determine the arrow key
                        case 'A':
                            this->SmartInputBuffer = 'W';
                            break;
                        case 'B':
                            this->SmartInputBuffer = 'S';
                            break;
                        case 'C':
                            this->SmartInputBuffer = 'D';
                            break;
                        case 'D':
                            this->SmartInputBuffer = 'A';
                            break;
                    }
                }
            } else {
              this->SmartInputBuffer =  Key;
            }

     
          }

          inline char SmartInput(){
            char Key = getchar();
            if (Key == 27) { // Check if it's an escape sequence
                if (getchar() == '[') { // Verify the next character
                    switch (getchar()) { // Get the third character to determine the arrow key
                        case 'A':
                            return 'W';
                            break;
                        case 'B':
                            return 'S';
                            break;
                        case 'C':
                            return 'D';
                            break;
                        case 'D':
                            return 'A';
                            break;
                    }
                }
            }
             
           return Key;
     

          }

          inline int NBInput(char *c, int len, int &count, const char data, char delimiter = '\n'){

            // delete char as soon as possible
              if((int)data == 127 && count > 0){
                  count = count - 1;
                  c[count] = ' ';
              }

              if(count < len-1 && count >=0 ){
                  if(data == delimiter){
                      c[count] = '\0';
                      return 1;
                  }
                  if(data >31 && data < 127){
                      c[count] = (char)data;
                      count = count +1;
                  }
                  //if((int)data == 127 && count > 0){
                  //    count = count - 1;
                  //    c[count] = ' ';
                  //}
        
                  return 0;
              }

            // return if text is to long
            if(data == delimiter){
                return 1;
            }

            return 0;


          }


          inline char RawInput(){
            return getchar();
          }

          inline void Restore(){
            tcsetattr(STDIN_FILENO, TCSANOW, &this->oldSettings);
            fcntl(STDIN_FILENO, F_SETFL, this->OldSystem_IOState);
          }


          // Typically used for mannulay blocking input

          inline void IO_NONBLOCK(){
              fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL) | O_NONBLOCK);
          }
          inline void IO_BLOCK(){
              fcntl(STDIN_FILENO, F_SETFL, this->OldSystem_IOState);
          }


        } Input;

        typedef struct Display{
            
            int Width;
            int Height;

            Pixel Buffer[Max_Height][Max_Width];

            // Heigh Width


             

            //set as defaults cause i like that size 
            Display(int Width = 79, int Height = 23) : Width(Width), Height(Height){}
            ~Display(){
                /*
                for(int i = 0; i < Max_Height; i++){
                    for(int j = 0; j < Max_Width; j++){
                        free((char *)this->Buffer[i][j].Color);
                        free((char *)this->Buffer[i][j].Body);
                    }
                }
                */
            }


            inline void SetPixel(int X, int Y, const char *Body, const char *Color = Color_Off){
                if(X < 0 || X > this->Width){
                    return;
                }
                if(Y < 0 || Y > this->Height){
                    return;
                }
               
                EasyColor(Color,this->Buffer[Y][X].Color);
                EasyColor(Body,this->Buffer[Y][X].Body);
            }

            inline void PutPixel(int X, int Y, Pixel &C){
                if(X < 0 || X > this->Width){
                    return;
                }
                if(Y < 0 || Y > this->Height){
                    return;
                }
                this->Buffer[Y][X] = C;
            }

            inline void ClearPixels(const char *Body, const char *Color,int x1 =0, int y1=0, int x2=Max_Width, int y2=Max_Height){
                for(int i = y1; i < y2; i++){
                    for(int j = x1; j < x2; j++){
                        EasyColor(Color,this->Buffer[i][j].Color);
                        EasyBody(Body,this->Buffer[i][j].Body);
                    }
                }
            }

            inline void Line(int x1,int y1, int x2, int y2, Pixel &C){
                int dx = abs(x2 - x1);
                int dy = abs(y2 - y1);
                int sx = x1 < x2 ? 1 : -1;
                int sy = y1 < y2 ? 1 : -1;
                int err = dx - dy;

                while (x1 != x2 || y1 != y2) {
                    this->PutPixel(x1,y1,C);
                    int e2 = err * 2;
                    if (e2 > -dy) {
                        err -= dy;
                        x1 += sx;
                    }
                    if (e2 < dx) {
                        err += dx;
                        y1 += sy;
                    }
                    this->PutPixel(x1,y1,C);
                }

            }

           

            inline void Triangle(int x1, int y1, int x2, int y2, int x3, int y3, Pixel C){
                this->Line(x1,y1,x2,y2,C);
                this->Line(x2,y2,x3,y3,C);
                this->Line(x3,y3,x1,y1,C);
            }

        inline void Rect(int TopX, int TopY, int BottomX, int BottomY, Pixel C, bool fill = false){
            if(fill){
                for(int i = TopY; i < BottomY; i++){
                for(int j = TopX; j < BottomX; j++){
                    EasyColor(C.Color,this->Buffer[i][j].Color);
                    EasyBody(C.Body,this->Buffer[i][j].Body);
                    }
                }
            } else {
                for(int i = TopY; i < BottomY; i++){
                        EasyColor(C.Color,this->Buffer[i][TopX].Color);
                        EasyBody(C.Body,this->Buffer[i][TopX].Body);

                        EasyColor(C.Color,this->Buffer[i][BottomX].Color);
                        EasyBody(C.Body,this->Buffer[i][BottomX].Body);
                    }
                
                // used J just to keep come consistansy 
                for(int j = TopX; j < BottomX; j++){
                        EasyColor(C.Color,this->Buffer[TopY][j].Color);
                        EasyBody(C.Body,this->Buffer[TopY][j].Body);

                        EasyColor(C.Color,this->Buffer[BottomY][j].Color);
                        EasyBody(C.Body,this->Buffer[BottomY][j].Body);
                    }
                    
                }
        }

        inline void PutText(int X, int Y, const char *Text, char const *Color = Color_Off, Direction dir = LEFT, Direction wdir = DOWN, int WrapLength = 80){
            const char  * temp = Text; // first copy the pointer to not change the original
            char *word = new char[2];
            int i = 0;
            int tX = X;
            int tY = Y;
            while(*temp != '\0'){
                i += 1;
                if(i == WrapLength){
                  i = 1;
                  //tX = X - tX;
                  //tY = Y - tY;
                  switch(wdir){
                    case DOWN:
                        tY++;
                        break;
                    case UP:
                        tY--;
                        break;
                    case LEFT:
                        tX++;
                        break;
                    case RIGHT:
                        tX--; 
                        break;

                  };

                  X = tX;
                  Y = tY;
                }

                //this->PutPixel(X,Y,*temp);
                //this->SetPixel(X,Y,EasyChar(*temp),Color);
                EasyChar(*temp,word);
                this->SetPixel(X,Y,word,Color);

                switch(dir){
                    case DOWN:
                        Y++;
                        break;
                    case UP:
                        Y--;
                        break;
                    case LEFT:
                        X++;
                        break;
                    case RIGHT:
                        X--; 
                        break;

                };

                temp++;

            }
            delete [] word;
            return;
        }

        inline void LimitPutText(int X, int Y, const char *Text, const char *Color, int limit, Direction dir = LEFT, Direction wdir = DOWN, int WrapLength = 80){
            const char  * temp = Text; // first copy the pointer to not change the original
            char *word = new char[2];
            int count = 0;
            int i = 0;
            int tX = X;
            int tY = Y;
            bool loop = true;
            if(limit == 0){
                return;
            }
            while(loop){
                i += 1;
                count += 1;
                if(i == WrapLength){
                  i = 1;
                  //tX = X - tX;
                  //tY = Y - tY;
                  switch(wdir){
                    case DOWN:
                        tY--;
                        break;
                    case UP:
                        tY++;
                        break;
                    case LEFT:
                        tX++;
                        break;
                    case RIGHT:
                        tX--; 
                        break;

                  };

                  X = tX;
                  Y = tY;
                }

                //this->Buffer[X][Y] = *temp;
                EasyChar(*temp,word);
                this->SetPixel(X,Y,word,Color);

                switch(dir){
                    case DOWN:
                        Y--;
                        break;
                    case UP:
                        Y++;
                        break;
                    case LEFT:
                        X++;
                        break;
                    case RIGHT:
                        X--; 
                        break;

                };

                temp++;


                if(*temp == '\0'){
                    loop = false;
                }
                if(count == limit){
                    loop = false;
                }

            }
            delete [] word;
            return;
        }

        inline void ClearPutText(int X, int Y, char const *Text, char const *Clear,const char *Color, Direction dir = LEFT, Direction wdir = DOWN, int WrapLength = 80){
            PutText(X,Y,Clear,Color,dir,wdir,WrapLength);
            PutText(X,Y,Text,Color,dir,wdir,WrapLength);
        }   

        // LimitedPutText
        //
        inline void Print(int x, int y, char *c)
        {
            printf("\033[%d;%dH%s", x, y, c);
        }
       
        //recomended for end screens
        inline void StaticShow(){
            printf("\n\r");
            for(int i = 0 ; i <= this->Height; i++){
                for(int j = 0; j <= this->Width; j++){
                    printf("%s",this->Buffer[i][j].Color);
                    printf("%s",this->Buffer[i][j].Body);
                }
                printf("\n\r");
            }
        }

        inline void Show(){
            for(int i = this->Height; i >= 0; i--){
                for(int j = this->Width; j>=0; j--){
                    Print(i,j+1,this->Buffer[i][j].Color);
                    Print(i,j+1,this->Buffer[i][j].Body);
                }
                printf("\n\r");
            }

        }


        inline void AltShow(Display &screen){
            printf("\n\r");
            for(int i = screen.Height; i >= 0; i--){
                for(int j = screen.Width; j>=0; j--){
                    Print(i,j+1,screen.Buffer[i][j].Color);
                    Print(i,j+1,screen.Buffer[i][j].Body);
                }
                printf("\n\r");
                }
        }

        inline void StaticAltShow(Display &screen){
            printf("\n\r");
            for(int i = 0; i <= screen.Height; i++){
                for(int j = 0; j <= screen.Width; j++){
                    printf("%s",screen.Buffer[i][j].Color);
                    printf("%s",screen.Buffer[i][j].Body);
                }
                printf("\n\r");
            }
        }


    } Display;

}

#endif
