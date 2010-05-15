/**
 *  Game Develop
 *  2008-2010 Florian Rival (Florian.Rival@gmail.com)
 */

#include <vector>
#include <string>
#include "GDL/Object.h"
#include <cmath>
#include "GDL/cPos.h"
#include "GDL/Event.h"
#include <iostream>
#include <sstream>
#include "GDL/Chercher.h"
#include "GDL/CommonTools.h"
#include "GDL/Force.h"
#include <iostream>
#include "GDL/Access.h"
#include <SFML/Window.hpp>
#include "GDL/RuntimeScene.h"
#include "GDL/gpl.h"
#include "GDL/ObjectsConcerned.h"
#include "GDL/Instruction.h"

/**
 * Test X position of an object
 */
bool Object::CondPosX( RuntimeScene & scene, ObjectsConcerned & objectsConcerned, const Instruction & condition )
{
    //optimisation : le test de signe en premier
    if (( condition.GetParameter( 2 ).GetAsCompOperator() == GDExpression::Equal && GetX() == condition.GetParameter( 1 ).GetAsMathExpressionResult(scene, objectsConcerned, shared_from_this() ) ) ||
            ( condition.GetParameter( 2 ).GetAsCompOperator() == GDExpression::Inferior && GetX() < condition.GetParameter( 1 ).GetAsMathExpressionResult(scene, objectsConcerned, shared_from_this() ) ) ||
            ( condition.GetParameter( 2 ).GetAsCompOperator() == GDExpression::Superior && GetX() > condition.GetParameter( 1 ).GetAsMathExpressionResult(scene, objectsConcerned, shared_from_this() ) ) ||
            ( condition.GetParameter( 2 ).GetAsCompOperator() == GDExpression::InferiorOrEqual && GetX() <= condition.GetParameter( 1 ).GetAsMathExpressionResult(scene, objectsConcerned, shared_from_this() ) ) ||
            ( condition.GetParameter( 2 ).GetAsCompOperator() == GDExpression::SuperiorOrEqual && GetX() >= condition.GetParameter( 1 ).GetAsMathExpressionResult(scene, objectsConcerned, shared_from_this() ) ) ||
            ( condition.GetParameter( 2 ).GetAsCompOperator() == GDExpression::Different && GetX() != condition.GetParameter( 1 ).GetAsMathExpressionResult(scene, objectsConcerned, shared_from_this() ) )
       )
    {
        return true;
    }

    return false;
}

/**
 * Test Y position of an object
 */
bool Object::CondPosY( RuntimeScene & scene, ObjectsConcerned & objectsConcerned, const Instruction & condition )
{
    //optimisation : le test de signe en premier
    if (( condition.GetParameter( 2 ).GetAsCompOperator() == GDExpression::Equal && GetY() == condition.GetParameter( 1 ).GetAsMathExpressionResult(scene, objectsConcerned, shared_from_this() ) ) ||
            ( condition.GetParameter( 2 ).GetAsCompOperator() == GDExpression::Inferior && GetY() < condition.GetParameter( 1 ).GetAsMathExpressionResult(scene, objectsConcerned, shared_from_this() ) ) ||
            ( condition.GetParameter( 2 ).GetAsCompOperator() == GDExpression::Superior && GetY() > condition.GetParameter( 1 ).GetAsMathExpressionResult(scene, objectsConcerned, shared_from_this() ) ) ||
            ( condition.GetParameter( 2 ).GetAsCompOperator() == GDExpression::InferiorOrEqual && GetY() <= condition.GetParameter( 1 ).GetAsMathExpressionResult(scene, objectsConcerned, shared_from_this() ) ) ||
            ( condition.GetParameter( 2 ).GetAsCompOperator() == GDExpression::SuperiorOrEqual && GetY() >= condition.GetParameter( 1 ).GetAsMathExpressionResult(scene, objectsConcerned, shared_from_this() ) ) ||
            ( condition.GetParameter( 2 ).GetAsCompOperator() == GDExpression::Different && GetY() != condition.GetParameter( 1 ).GetAsMathExpressionResult(scene, objectsConcerned, shared_from_this() ) )
       )
    {
        return true;
    }

    return false;
}

////////////////////////////////////////////////////////////
/// Test la distance d'un objet � un autre
///
/// Type : Distance
/// Param�tre 1 : Objet
/// Param�tre 2 : Objet
/// Param�tre 3 : Valeur
/// Param�tre 4 : Signe du test
////////////////////////////////////////////////////////////
bool CondDistance( RuntimeScene & scene, ObjectsConcerned & objectsConcerned, const Instruction & condition )
{
    ObjectsConcerned objectsConcernedForExpressions = objectsConcerned;

    ObjList list = objectsConcerned.PickAndRemove(condition.GetParameter( 0 ).GetAsObjectIdentifier(), condition.IsGlobal());
    ObjList list2 = objectsConcerned.PickAndRemove(condition.GetParameter( 1 ).GetAsObjectIdentifier(), condition.IsGlobal());
    if ( condition.GetParameter( 1 ).GetPlainString() == condition.GetParameter( 0 ).GetPlainString())
        list2 = list;
    bool isTrue = false;

	ObjList::iterator obj = list.begin();
	ObjList::const_iterator obj_end = list.end();
    for ( ; obj != obj_end; ++obj )
    {
        ObjList::iterator obj2 = list2.begin();
        ObjList::const_iterator obj2_end = list2.end();
        for ( ; obj2 != obj2_end; ++obj2 )
        {
            //Enfin, on teste vraiment.
            if ( *obj != *obj2 )
            {
                float X = (*obj)->GetDrawableX()+(*obj)->GetCenterX() - ((*obj2)->GetDrawableX()+(*obj2)->GetCenterX());
                float Y = (*obj)->GetDrawableY()+(*obj)->GetCenterY() - ((*obj2)->GetDrawableY()+(*obj2)->GetCenterY());

                //optimisation : le test de signe en premier
                if (( condition.GetParameter( 3 ).GetAsCompOperator() == GDExpression::Equal && gpl::sqrt(X*X+Y*Y) == condition.GetParameter( 2 ).GetAsMathExpressionResult(scene, objectsConcernedForExpressions, *obj, *obj2 ) ) ||
                        ( condition.GetParameter( 3 ).GetAsCompOperator() == GDExpression::Inferior && gpl::sqrt(X*X+Y*Y) < condition.GetParameter( 2 ).GetAsMathExpressionResult(scene, objectsConcernedForExpressions, *obj, *obj2 ) ) ||
                        ( condition.GetParameter( 3 ).GetAsCompOperator() == GDExpression::Superior && gpl::sqrt(X*X+Y*Y) > condition.GetParameter( 2 ).GetAsMathExpressionResult(scene, objectsConcernedForExpressions, *obj, *obj2 ) ) ||
                        ( condition.GetParameter( 3 ).GetAsCompOperator() == GDExpression::InferiorOrEqual && gpl::sqrt(X*X+Y*Y) <= condition.GetParameter( 2 ).GetAsMathExpressionResult(scene, objectsConcernedForExpressions, *obj, *obj2 ) ) ||
                        ( condition.GetParameter( 3 ).GetAsCompOperator() == GDExpression::SuperiorOrEqual && gpl::sqrt(X*X+Y*Y) >= condition.GetParameter( 2 ).GetAsMathExpressionResult(scene, objectsConcernedForExpressions, *obj, *obj2 ) ) ||
                        ( condition.GetParameter( 3 ).GetAsCompOperator() == GDExpression::Different && gpl::sqrt(X*X+Y*Y) != condition.GetParameter( 2 ).GetAsMathExpressionResult(scene, objectsConcernedForExpressions, *obj, *obj2 ) )
                   )
                {
                    if ( !condition.IsInverted() )
                    {
                        isTrue = true;
                        objectsConcerned.objectsPicked.AddObject( *obj ); //L'objet est ajout� aux objets concern�s ( Il n'y est pas d�j� )
                        objectsConcerned.objectsPicked.AddObject( *obj2 ); //L'objet est ajout� aux objets concern�s ( Il n'y est pas d�j� )
                    }
                }
                else
                {
                    if ( condition.IsInverted() )
                    {
                        isTrue = true;
                        objectsConcerned.objectsPicked.AddObject( *obj ); //L'objet est ajout� aux objets concern�s ( Il n'y est pas d�j� )
                        objectsConcerned.objectsPicked.AddObject( *obj2 ); //L'objet est ajout� aux objets concern�s ( Il n'y est pas d�j� )
                    }
                }
            }
        }
    }

    return isTrue;
}
