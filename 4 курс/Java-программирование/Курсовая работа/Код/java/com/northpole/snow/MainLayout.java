package com.northpole.snow;

import com.northpole.snow.db.AccessDatabaseService;
import com.vaadin.flow.component.applayout.AppLayout;
import com.vaadin.flow.component.applayout.DrawerToggle;
import com.vaadin.flow.component.details.Details;
import com.vaadin.flow.component.html.H1;
import com.vaadin.flow.component.orderedlayout.VerticalLayout;
import com.vaadin.flow.component.orderedlayout.HorizontalLayout;
import com.vaadin.flow.component.orderedlayout.FlexComponent;
import com.vaadin.flow.component.sidenav.SideNav;
import com.vaadin.flow.component.sidenav.SideNavItem;
import com.vaadin.flow.router.PageTitle;
import com.vaadin.flow.theme.lumo.LumoUtility;
import com.vaadin.flow.component.icon.VaadinIcon;

import java.net.URLEncoder;
import java.nio.charset.StandardCharsets;

@PageTitle("Access DB App")
public class MainLayout extends AppLayout {

    public MainLayout(AccessDatabaseService db) {
        getElement().getStyle().set("--vaadin-app-layout-drawer-width", "290px");

        DrawerToggle toggle = new DrawerToggle();
        H1 title = new H1("Общественный транспорт г. Череповца");
        title.addClassNames(LumoUtility.FontSize.LARGE, LumoUtility.Margin.NONE);

        HorizontalLayout header = new HorizontalLayout(toggle, title);
        header.setDefaultVerticalComponentAlignment(FlexComponent.Alignment.CENTER);
        header.setWidthFull();
        header.addClassNames(LumoUtility.Padding.Horizontal.MEDIUM, LumoUtility.Padding.Vertical.SMALL);

        addToNavbar(header);

        SideNav dashboardNav = new SideNav();
        dashboardNav.addItem(new SideNavItem("Дэшборд", MainView.class, VaadinIcon.DASHBOARD.create()));

        SideNav reportsNav = new SideNav();
        for (String report : ReportsView.createPresets().keySet()) {
            String encoded = URLEncoder.encode(report, StandardCharsets.UTF_8);
            reportsNav.addItem(new SideNavItem(report, "report/" + encoded, VaadinIcon.SEARCH.create()));
        }

        SideNav tablesNav = new SideNav();
        try {
            for (var t : db.listTables()) {
                String encoded = URLEncoder.encode(t.name(), StandardCharsets.UTF_8);
                tablesNav.addItem(new SideNavItem(t.name(), "table/" + encoded, VaadinIcon.TABLE.create()));
            }
        } catch (Exception ex) {
            tablesNav.addItem(new SideNavItem("База данных недоступна", MainView.class, VaadinIcon.WARNING.create()));
        }

        Details reports = new Details("Запросы", reportsNav);
        reports.setOpened(true);

        Details tables = new Details("Таблицы", tablesNav);
        tables.setOpened(true);

        VerticalLayout drawer = new VerticalLayout(dashboardNav, reports, tables);
        drawer.setPadding(false);
        drawer.setSpacing(false);

        addToDrawer(drawer);
    }
}
