package com.northpole.snow;

import com.northpole.snow.db.AccessDatabaseService;
import com.vaadin.flow.component.button.Button;
import com.vaadin.flow.component.html.H2;
import com.vaadin.flow.component.html.Div;
import com.vaadin.flow.component.html.H3;
import com.vaadin.flow.component.html.Span;
import com.vaadin.flow.component.icon.VaadinIcon;
import com.vaadin.flow.component.notification.Notification;
import com.vaadin.flow.component.orderedlayout.HorizontalLayout;
import com.vaadin.flow.component.orderedlayout.FlexComponent;
import com.vaadin.flow.component.orderedlayout.VerticalLayout;
import com.vaadin.flow.router.PageTitle;
import com.vaadin.flow.router.Route;
import java.util.List;

@PageTitle("Дэшборд")
@Route(value = "", layout = MainLayout.class)
public class MainView extends VerticalLayout {

    private final AccessDatabaseService db;

    private final Span routesCount = new Span("-");
    private final Span stopsCount = new Span("-");
    private final Span carriersCount = new Span("-");

    private final Div chartRoutesByTransport = new Div();
    private final Div chartRoutesByCarrier = new Div();
    private final Div chartRoutesByRouteType = new Div();
    private final Div chartTopStops = new Div();
    private final Div donutPasses = new Div();
    private final Div donutTransfer = new Div();

    public MainView(AccessDatabaseService db) {
        this.db = db;

        setSizeFull();

        H2 title = new H2("Дэшборд по базе данных общественного транспорта");
        Button refresh = new Button("Обновить", VaadinIcon.REFRESH.create(), e -> load());

        HorizontalLayout actions = new HorizontalLayout(refresh);
        actions.setDefaultVerticalComponentAlignment(FlexComponent.Alignment.CENTER);

        Div routesKpi = kpiCard("Маршруты", routesCount);
        Div stopsKpi = kpiCard("Остановки", stopsCount);
        Div carriersKpi = kpiCard("Перевозчики", carriersCount);

        routesKpi.getStyle().set("grid-column", "span 4");
        stopsKpi.getStyle().set("grid-column", "span 4");
        carriersKpi.getStyle().set("grid-column", "span 4");

        chartRoutesByTransport.setWidthFull();
        chartRoutesByCarrier.setWidthFull();
        chartRoutesByRouteType.setWidthFull();
        chartTopStops.setWidthFull();
        donutPasses.setWidthFull();
        donutTransfer.setWidthFull();

        Div routesByTransportCard = chartCard("Маршруты по типу транспорта", chartRoutesByTransport);
        Div routesByCarrierCard = chartCard("Маршруты по перевозчикам", chartRoutesByCarrier);
        Div routesByRouteTypeCard = chartCard("Маршруты по типу", chartRoutesByRouteType);

        routesByTransportCard.getStyle().set("grid-column", "span 4");
        routesByCarrierCard.getStyle().set("grid-column", "span 4");
        routesByRouteTypeCard.getStyle().set("grid-column", "span 4");

        Div topStopsCard = chartCard("Остановки по маршрутам", chartTopStops);
        topStopsCard.setWidthFull();
        topStopsCard.getStyle().set("grid-column", "span 12");

        Div passesCard = chartCard("Тарифы: проездные", donutPasses);
        Div transferCard = chartCard("Тарифы: бесплатная пересадка", donutTransfer);

        passesCard.getStyle().set("grid-column", "span 6");
        transferCard.getStyle().set("grid-column", "span 6");

        Div dashboardGrid = new Div(
                routesKpi, stopsKpi, carriersKpi,
                routesByTransportCard, routesByCarrierCard, routesByRouteTypeCard,
                topStopsCard,
                passesCard, transferCard
        );
        dashboardGrid.setWidthFull();
        dashboardGrid.getStyle()
                .set("display", "grid")
                .set("grid-template-columns", "repeat(12, minmax(0, 1fr))")
                .set("gap", "12px")
                .set("align-items", "stretch")
                .set("max-width", "100%")
                .set("box-sizing", "border-box")
                .set("overflow-x", "hidden");

        add(title, actions, dashboardGrid);

        load();
    }

    private void load() {
        try {
            routesCount.setText(String.valueOf(db.countRows("Маршруты")));
            stopsCount.setText(String.valueOf(db.countRows("Остановки")));
            carriersCount.setText(String.valueOf(db.countRows("Перевозчики")));

            chartRoutesByTransport.removeAll();
            chartRoutesByCarrier.removeAll();
            chartRoutesByRouteType.removeAll();
            chartTopStops.removeAll();
            donutPasses.removeAll();
            donutTransfer.removeAll();

            chartRoutesByTransport.add(barChartSvg(db.routesByTransportType(8), 420, 220));
            chartRoutesByCarrier.add(barChartSvg(db.routesByCarrier(8), 420, 220));
            chartRoutesByRouteType.add(barChartSvg(db.routesByRouteType(8), 420, 220));
            chartTopStops.add(barChartSvg(db.topStopsByUsageInRoutes(10), 860, 260));

            var passes = db.routeTariffBoolSplit("Проездные");
            donutPasses.add(donutSvg(passes.yes(), passes.no(), "Да", "Нет", 260, 220));

            var transfer = db.routeTariffBoolSplit("Бесплатная пересадка");
            donutTransfer.add(donutSvg(transfer.yes(), transfer.no(), "Да", "Нет", 260, 220));
        } catch (Exception ex) {
            Notification.show("Ошибка чтения БД: " + ex.getMessage(), 5000, Notification.Position.MIDDLE);
        }
    }

    private static Div kpiCard(String title, Span value) {
        Div card = new Div();
        card.getStyle()
                .set("border", "1px solid var(--lumo-contrast-10pct)")
                .set("border-radius", "12px")
                .set("padding", "12px 14px")
                .set("min-width", "0")
                .set("background", "var(--lumo-base-color)")
                .set("max-width", "100%")
                .set("box-sizing", "border-box")
                .set("overflow", "hidden")
                .set("height", "160px")
                .set("min-height", "160px")
                .set("display", "flex")
                .set("flex-direction", "column")
                .set("justify-content", "center")
                .set("align-items", "flex-start");

        Span t = new Span(title);
        t.getStyle().set("color", "var(--lumo-secondary-text-color)");
        value.getStyle()
                .set("display", "block")
                .set("font-size", "28px")
                .set("font-weight", "600")
                .set("margin-top", "6px")
                .set("line-height", "1.1");

        card.add(t, value);
        return card;
    }

    private static Div chartCard(String title, Div content) {
        Div card = new Div();
        card.setWidthFull();
        card.getStyle()
                .set("border", "1px solid var(--lumo-contrast-10pct)")
                .set("border-radius", "12px")
                .set("padding", "12px 14px")
                .set("background", "var(--lumo-base-color)")
                .set("display", "flex")
                .set("flex-direction", "column")
                .set("min-height", "320px")
                .set("min-width", "0")
                .set("max-width", "100%")
                .set("box-sizing", "border-box")
                .set("overflow", "hidden");

        H3 h = new H3(title);
        h.getStyle().set("margin", "0 0 10px 0");

        content.getStyle().set("flex", "1").set("min-width", "0").set("max-width", "100%");

        card.add(h, content);
        return card;
    }

    private static Div barChartSvg(List<AccessDatabaseService.Stat> stats, int width, int height) {
        Div host = new Div();
        host.getStyle().set("min-width", "0").set("overflow", "hidden");

        if (stats == null || stats.isEmpty()) {
            Span empty = new Span("Нет данных");
            empty.getStyle().set("color", "var(--lumo-secondary-text-color)");
            host.add(empty);
            return host;
        }

        int max = 1;
        int maxLabelLen = 0;
        for (var s : stats) {
            max = Math.max(max, s.value());
            String lbl = s.label() == null ? "" : s.label().trim();
            maxLabelLen = Math.max(maxLabelLen, Math.min(28, lbl.length()));
        }

        // Make bars use almost all the card width.
        // Keep a small label column, truncate labels harder, and place values near bar end.
        int leftPad = Math.min(160, Math.max(90, maxLabelLen * 6 + 16));
        int rightPad = 6;
        int valuePad = 0;
        int topPad = 8;
        int bottomPad = 14;
        int plotW = Math.max(1, width - leftPad - rightPad);
        int barMaxW = Math.max(1, plotW - valuePad);
        int plotH = Math.max(1, height - topPad - bottomPad);

        int barGap = 8;
        int barH = Math.max(10, (plotH - barGap * (stats.size() - 1)) / stats.size());

        StringBuilder sb = new StringBuilder();
        sb.append("<svg xmlns='http://www.w3.org/2000/svg' width='100%' height='")
                .append(height)
                .append("' viewBox='0 0 ")
                .append(width)
                .append(" ")
                .append(height)
                .append("'>");

        sb.append("<rect x='0' y='0' width='")
                .append(width)
                .append("' height='")
                .append(height)
                .append("' fill='transparent'/>");

        for (int i = 0; i < stats.size(); i++) {
            var s = stats.get(i);
            int y = topPad + i * (barH + barGap);
            int barW = (int) Math.round((s.value() * 1.0 / max) * barMaxW);
            String label = escapeXml(trimTo(s.label(), 28));

            // Right-align labels at the edge of the label column so they never overlap bars.
            sb.append("<text x='")
                    .append(Math.max(8, leftPad - 6))
                    .append("' y='")
                    .append(y + barH - 2)
                    .append("' text-anchor='end' font-size='12' fill='var(--lumo-body-text-color)'>")
                    .append(label)
                    .append("</text>");

            sb.append("<rect x='")
                    .append(leftPad)
                    .append("' y='")
                    .append(y)
                    .append("' width='")
                    .append(Math.max(1, barW))
                    .append("' height='")
                    .append(barH)
                    .append("' rx='6' ry='6' fill='var(--lumo-primary-color)' opacity='0.85' />");

            // Prefer placing value inside the bar end; if too small, place it after the bar.
            int valueXInside = leftPad + Math.max(8, barW - 6);
            boolean inside = barW >= 26;
            int valueX = inside ? valueXInside : (leftPad + barW + 6);
            String valueFill = inside ? "var(--lumo-base-color)" : "var(--lumo-body-text-color)";
            String anchor = inside ? "end" : "start";

            sb.append("<text x='")
                    .append(valueX)
                    .append("' y='")
                    .append(y + barH - 2)
                    .append("' text-anchor='")
                    .append(anchor)
                    .append("' font-size='12' fill='")
                    .append(valueFill)
                    .append("'>")
                    .append(s.value())
                    .append("</text>");
        }

        sb.append("</svg>");

        host.setWidthFull();
        host.getElement().setProperty("innerHTML", sb.toString());
        return host;
    }

    private static Div donutSvg(int yes, int no, String yesLabel, String noLabel, int width, int height) {
        Div host = new Div();
        int total = Math.max(0, yes) + Math.max(0, no);
        if (total <= 0) {
            Span empty = new Span("Нет данных");
            empty.getStyle().set("color", "var(--lumo-secondary-text-color)");
            host.add(empty);
            return host;
        }

        double yesPct = yes * 1.0 / total;
        double noPct = 1.0 - yesPct;

        int cx = width / 2;
        int cy = height / 2 - 8;
        int rOuter = Math.min(width, height) / 2 - 26;
        int rInner = (int) Math.round(rOuter * 0.62);

        String yesColor = "var(--lumo-primary-color)";
        String noColor = "var(--lumo-contrast-30pct)";

        StringBuilder sb = new StringBuilder();
        sb.append("<svg xmlns='http://www.w3.org/2000/svg' width='")
                .append(width)
                .append("' height='")
                .append(height)
                .append("' viewBox='0 0 ")
                .append(width)
                .append(" ")
                .append(height)
                .append("'>");

        // background ring (no)
        sb.append(ringArc(cx, cy, rOuter, rInner, 0.0, 1.0, noColor));
        // yes arc on top
        sb.append(ringArc(cx, cy, rOuter, rInner, 0.0, yesPct, yesColor));

        sb.append("<text x='").append(cx).append("' y='").append(cy + 5)
                .append("' text-anchor='middle' font-size='18' font-weight='600' fill='var(--lumo-body-text-color)'>")
                .append((int) Math.round(yesPct * 100)).append("%</text>");

        sb.append("<text x='").append(cx).append("' y='").append(cy + 24)
                .append("' text-anchor='middle' font-size='12' fill='var(--lumo-secondary-text-color)'>")
                .append(escapeXml(yesLabel)).append(": ").append(yes)
                .append("  •  ")
                .append(escapeXml(noLabel)).append(": ").append(no)
                .append("</text>");

        sb.append("</svg>");

        host.getElement().setProperty("innerHTML", sb.toString());
        return host;
    }

    private static String ringArc(int cx, int cy, int rOuter, int rInner, double startPct, double sweepPct, String fill) {
        // start at -90deg, clockwise
        double start = -Math.PI / 2 + 2 * Math.PI * startPct;
        double end = start + 2 * Math.PI * sweepPct;

        if (sweepPct <= 0) {
            return "";
        }
        if (sweepPct >= 0.999999) {
            // full ring: draw as two arcs to avoid SVG full-arc edge cases
            return ringArc(cx, cy, rOuter, rInner, 0.0, 0.5, fill)
                    + ringArc(cx, cy, rOuter, rInner, 0.5, 0.5, fill);
        }

        double x1o = cx + rOuter * Math.cos(start);
        double y1o = cy + rOuter * Math.sin(start);
        double x2o = cx + rOuter * Math.cos(end);
        double y2o = cy + rOuter * Math.sin(end);

        double x1i = cx + rInner * Math.cos(end);
        double y1i = cy + rInner * Math.sin(end);
        double x2i = cx + rInner * Math.cos(start);
        double y2i = cy + rInner * Math.sin(start);

        int largeArc = sweepPct > 0.5 ? 1 : 0;

        StringBuilder d = new StringBuilder();
        d.append("M ").append(x1o).append(" ").append(y1o).append(" ");
        d.append("A ").append(rOuter).append(" ").append(rOuter).append(" 0 ").append(largeArc).append(" 1 ")
                .append(x2o).append(" ").append(y2o).append(" ");
        d.append("L ").append(x1i).append(" ").append(y1i).append(" ");
        d.append("A ").append(rInner).append(" ").append(rInner).append(" 0 ").append(largeArc).append(" 0 ")
                .append(x2i).append(" ").append(y2i).append(" Z");

        return "<path d='" + d + "' fill='" + fill + "'/>";
    }

    private static String trimTo(String s, int max) {
        if (s == null) {
            return "";
        }
        String t = s.trim();
        if (t.length() <= max) {
            return t;
        }
        return t.substring(0, Math.max(0, max - 1)) + "…";
    }

    private static String escapeXml(String s) {
        if (s == null) {
            return "";
        }
        return s
                .replace("&", "&amp;")
                .replace("<", "&lt;")
                .replace(">", "&gt;")
                .replace("\"", "&quot;")
                .replace("'", "&apos;");
    }
}