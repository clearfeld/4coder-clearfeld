function void
cl_draw_margin(Application_Links *app, Rect_f32 outer, Rect_f32 inner, ARGB_Color color){
    //draw_rectangle(app, Rf32(outer.x0, outer.y0, outer.x1, inner.y0), 0.f, color);
    //draw_rectangle(app, Rf32(outer.x0, inner.y1, outer.x1, outer.y1), 0.f, color);
    draw_rectangle(app, Rf32(outer.x0, inner.y0, inner.x0, inner.y1), 0.f, color);
    draw_rectangle(app, Rf32(inner.x1, inner.y0, outer.x1, inner.y1), 0.f, color);
}

function void
cl_draw_margin(Application_Links *app, Rect_f32 outer, Rect_f32 inner, FColor color){
    ARGB_Color argb = fcolor_resolve(color);
    cl_draw_margin(app, outer, inner, argb);
}

function Rect_f32
cl_draw_background_and_margin(Application_Links *app, View_ID view, ARGB_Color margin, ARGB_Color back){
    Rect_f32 view_rect = view_get_screen_rect(app, view);
    Rect_f32 inner = rect_inner(view_rect, 1.f);
    inner.y0 -= 1.f;
    inner.y1 += 1.f;

    draw_rectangle(app, inner, 0.f, back);
    cl_draw_margin(app, view_rect, inner, margin);
    return(inner);
}

function Rect_f32
cl_draw_background_and_margin(Application_Links *app, View_ID view, FColor margin, FColor back){
    ARGB_Color margin_argb = fcolor_resolve(margin);
    ARGB_Color back_argb = fcolor_resolve(back);
    return(cl_draw_background_and_margin(app, view, margin_argb, back_argb));
}

function Rect_f32
cl_draw_background_and_margin(Application_Links *app, View_ID view, b32 is_active_view){
    FColor margin_color = get_panel_margin_color(is_active_view?UIHighlight_Active:UIHighlight_None);
    FColor background_color = fcolor_id(defcolor_back);
    // if(is_active_view) {
    //     background_color = ACTIVE_VIEW_BACKGROUND_COLOR;
    // }

    return(cl_draw_background_and_margin(app, view, margin_color, background_color));
}
