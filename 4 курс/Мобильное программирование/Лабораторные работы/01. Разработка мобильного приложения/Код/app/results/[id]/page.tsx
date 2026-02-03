import React from "react";
import ResultsPageClient from "@/components/ResultsPageClient";

interface ResultsPageProps {
  params: Promise<{
    id: string;
  }>;
}

export default async function ResultsPage({ params }: ResultsPageProps) {
  const { id: groupCode } = await params;
  // Нормализуем код группы (верхний регистр, без пробелов)
  const normalizedCode = groupCode?.toUpperCase().trim() || groupCode;
  return <ResultsPageClient groupCode={normalizedCode} />;
}
